#include "userprog/exception.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>
#include "userprog/gdt.h"
#include "threads/interrupt.h"
#include "threads/vaddr.h"
#include "threads/malloc.h"
#include "userprog/syscall.h"
#include "userprog/pagedir.h"
#include "vm/page.h"
#include "vm/frame.h"
#include "vm/swap.h"

/* Number of page faults processed. */
static long long page_fault_cnt;

static void kill (struct intr_frame *);
static void page_fault (struct intr_frame *);

/* Registers handlers for interrupts that can be caused by user
   programs.

   In a real Unix-like OS, most of these interrupts would be
   passed along to the user process in the form of signals, as
   described in [SV-386] 3-24 and 3-25, but we don't implement
   signals.  Instead, we'll make them simply kill the user
   process.

   Page faults are an exception.  Here they are treated the same
   way as other exceptions, but this will need to change to
   implement virtual memory.

   Refer to [IA32-v3a] section 5.15 "Exception and Interrupt
   Reference" for a description of each of these exceptions. */
void
exception_init (void) 
{
  /* These exceptions can be raised explicitly by a user program,
     e.g. via the INT, INT3, INTO, and BOUND instructions.  Thus,
     we set DPL==3, meaning that user programs are allowed to
     invoke them via these instructions. */
  intr_register_int (3, 3, INTR_ON, kill, "#BP Breakpoint Exception");
  intr_register_int (4, 3, INTR_ON, kill, "#OF Overflow Exception");
  intr_register_int (5, 3, INTR_ON, kill,
                     "#BR BOUND Range Exceeded Exception");

  /* These exceptions have DPL==0, preventing user processes from
     invoking them via the INT instruction.  They can still be
     caused indirectly, e.g. #DE can be caused by dividing by
     0.  */
  intr_register_int (0, 0, INTR_ON, kill, "#DE Divide Error");
  intr_register_int (1, 0, INTR_ON, kill, "#DB Debug Exception");
  intr_register_int (6, 0, INTR_ON, kill, "#UD Invalid Opcode Exception");
  intr_register_int (7, 0, INTR_ON, kill,
                     "#NM Device Not Available Exception");
  intr_register_int (11, 0, INTR_ON, kill, "#NP Segment Not Present");
  intr_register_int (12, 0, INTR_ON, kill, "#SS Stack Fault Exception");
  intr_register_int (13, 0, INTR_ON, kill, "#GP General Protection Exception");
  intr_register_int (16, 0, INTR_ON, kill, "#MF x87 FPU Floating-Point Error");
  intr_register_int (19, 0, INTR_ON, kill,
                     "#XF SIMD Floating-Point Exception");

  /* Most exceptions can be handled with interrupts turned on.
     We need to disable interrupts for page faults because the
     fault address is stored in CR2 and needs to be preserved. */
  intr_register_int (14, 0, INTR_OFF, page_fault, "#PF Page-Fault Exception");
}

/* Prints exception statistics. */
void
exception_print_stats (void) 
{
  printf ("Exception: %lld page faults\n", page_fault_cnt);
}

/* Handler for an exception (probably) caused by a user process. */
static void
kill (struct intr_frame *f) 
{
  /* This interrupt is one (probably) caused by a user process.
     For example, the process might have tried to access unmapped
     virtual memory (a page fault).  For now, we simply kill the
     user process.  Later, we'll want to handle page faults in
     the kernel.  Real Unix-like operating systems pass most
     exceptions back to the process via signals, but we don't
     implement them. */
     
  /* The interrupt frame's code segment value tells us where the
     exception originated. */
  switch (f->cs)
    {
    case SEL_UCSEG:
      /* User's code segment, so it's a user exception, as we
         expected.  Kill the user process.  */
      printf ("%s: dying due to interrupt %#04x (%s).\n",
              thread_name (), f->vec_no, intr_name (f->vec_no));
      intr_dump_frame (f);
      thread_exit (); 

    case SEL_KCSEG:
      /* Kernel's code segment, which indicates a kernel bug.
         Kernel code shouldn't throw exceptions.  (Page faults
         may cause kernel exceptions--but they shouldn't arrive
         here.)  Panic the kernel to make the point.  */
      intr_dump_frame (f);
      PANIC ("Kernel bug - unexpected interrupt in kernel"); 

    default:
      /* Some other code segment?  Shouldn't happen.  Panic the
         kernel. */
      printf ("Interrupt %#04x (%s) in unknown segment %04x\n",
             f->vec_no, intr_name (f->vec_no), f->cs);
      thread_exit ();
    }
}

static void sysExit (void){
  thread_current ()->exit_status = -1;
  thread_exit ();
}

static void stack_growth (struct thread *t){

  struct frame *earned_frame;
  void *kpage;
  struct page *fp_info;

  earned_frame = frame_alloc (PAL_ZERO);
  kpage = earned_frame->kpage;

  t->stack_end = (char *)(t->stack_end) - PGSIZE;
  
  fp_info = malloc (sizeof (struct page));
  fp_info->pd = t->pagedir;
  fp_info->upage = t->stack_end;
  fp_info->kpage = kpage;
  fp_info->in_file = false;
  fp_info->in_swap = false;
  fp_info->writable = true;
  fp_info->frame_index  = earned_frame;
  fp_info->mmapped = false;

  page_insert (t, fp_info);
  pagedir_set_page (t->pagedir, t->stack_end, kpage, true);
  pagedir_set_dirty (t->pagedir, t->stack_end, true);

  earned_frame->mmapped = false;
  earned_frame->upage = t->stack_end;
  earned_frame->frame_thread = t;
  earned_frame->pinned = false;
}

struct frame *
page_claim_and_set (struct thread *t, struct page *fp_info) {

  struct frame *earned_frame;
  void *kpage;
  bool is_dirty;

  /* read page and write page to frame */
  earned_frame = frame_alloc (0);
  kpage = earned_frame->kpage;

  if (fp_info->in_file){

    if (fp_info->read_bytes != 0){
   
      lock_acquire (&filesys_lock);
      
      file_seek (fp_info->page_file, fp_info->file_ofs);
      ASSERT (file_read (fp_info->page_file, kpage, 
            fp_info->read_bytes) == fp_info->read_bytes)
     
      lock_release (&filesys_lock);
    }

    memset ((char *)kpage + fp_info->read_bytes, 0, fp_info->zero_bytes);
  }
  else if (fp_info->in_swap) {

    swap_free (true, kpage, fp_info->swap_index);
    /* read page from swap partition */
  
  }
 
  if (pagedir_is_dirty (t->pagedir, fp_info->upage) && !fp_info->mmapped)
    is_dirty =  true;
  else
    is_dirty = false;

  /* add mappig form faulted upage to kpage */
  pagedir_set_page (t->pagedir, fp_info->upage, kpage, fp_info->writable);
  pagedir_set_dirty (t->pagedir, fp_info->upage, is_dirty);

  /* edit supplemental page table entry */
  fp_info->kpage = kpage;
  fp_info->in_file = false;
  fp_info->in_swap = false;
  fp_info->frame_index = earned_frame;

  earned_frame->mmapped = fp_info->mmapped;
  earned_frame->frame_file = fp_info->page_file;
  earned_frame->upage = fp_info->upage;
  earned_frame->frame_thread = t;
  earned_frame->read_bytes = fp_info->read_bytes;

  return earned_frame;
}

/* Page fault handler.  This is a skeleton that must be filled in
   to implement virtual memory.  Some solutions to project 2 may
   also require modifying this code.

   At entry, the address that faulted is in CR2 (Control Register
   2) and information about the fault, formatted as described in
   the PF_* macros in exception.h, is in F's error_code member.  The
   example code here shows how to parse that information.  You
   can find more information about both of these in the
   description of "Interrupt 14--Page Fault Exception (#PF)" in
   [IA32-v3a] section 5.15 "Exception and Interrupt Reference". */
static void
page_fault (struct intr_frame *f) 
{
  bool not_present;  /* True: not-present page, false: writing r/o page. */
  bool write;        /* True: access was write, false: access was read. */
  bool user;         /* True: access by user, false: access by kernel. */
  void *fault_addr;  /* Fault address. */
  void *fault_page;
  struct thread *t = thread_current ();
  struct frame *earned_frame;
  struct page *fp_info;
  
  /* Obtain faulting address, the virtual address that was
     accessed to cause the fault.  It may point to code or to
     data.  It is not necessarily the address of the instruction
     that caused the fault (that's f->eip).
     See [IA32-v2a] "MOV--Move to/from Control Registers" and
     [IA32-v3a] 5.15 "Interrupt 14--Page Fault Exception
     (#PF)". */
  asm ("movl %%cr2, %0" : "=r" (fault_addr));

  /* Turn interrupts back on (they were only off so that we could
     be assured of reading CR2 before it changed). */
  intr_enable ();

  /* Count page faults. */
  page_fault_cnt++;

  /* Determine cause. */
  not_present = (f->error_code & PF_P) == 0;
  write = (f->error_code & PF_W) != 0;
  user = (f->error_code & PF_U) != 0;

  /* writing to r/o page */
  if (!not_present)
    sysExit();

  /* page lies within kernel virtual memory */
  if (user && fault_addr >= 0xC0000000)
    sysExit();

  fault_page = pg_round_down (fault_addr);

  /* stack growth */
  if (user && f->esp < t->stack_end)
  {
    stack_growth (t);
    return ;
  }

  if ((uint32_t)fault_addr == ((uint32_t) f->esp) - 4
      || (uint32_t)fault_addr == ((uint32_t) f->esp) - 32)
  {
    if (user && t->stack_end > fault_addr)
    {
      stack_growth (t);
      return ;
    }

    ASSERT (pagedir_get_page (t->pagedir, fault_page) == NULL)
  }

  /* user process should not expect that any data at address */
  fp_info = page_search (t, fault_page);

  if (fp_info == NULL){
    sysExit ();
  }

  earned_frame = page_claim_and_set (t, fp_info);

  /* remove the pin of the frame */
  earned_frame->pinned = false;

}

