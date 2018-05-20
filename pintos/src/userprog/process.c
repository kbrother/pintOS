#include "userprog/process.h"
#include <debug.h>
#include <inttypes.h>
#include <round.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userprog/gdt.h"
#include "userprog/pagedir.h"
#include "userprog/tss.h"
#include "filesys/directory.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "threads/flags.h"
#include "threads/init.h"
#include "threads/interrupt.h"
#include "threads/palloc.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "userprog/syscall.h"
#include "vm/frame.h"
#include "vm/page.h"
#include "vm/swap.h"

static thread_func start_process NO_RETURN;
static bool load (const char *cmdline, void (**eip) (void), void **esp);

/* Starts a new thread running a user program loaded from
   FILENAME.  The new thread may be scheduled (and may even exit)
   before process_execute() returns.  Returns the new process's
   thread id, or TID_ERROR if the thread cannot be created. */
tid_t
process_execute (const char *file_name) 
{
	char *fn_copy;
  tid_t tid;
  struct thread *cur = thread_current ();

  /* Make a copy of FILE_NAME.
     Otherwise there's a race between the caller and load(). */
  fn_copy = palloc_get_page (0);
  if (fn_copy == NULL)
    return TID_ERROR;
  strlcpy (fn_copy, file_name, PGSIZE);

  /* Create a new thread to execute FILE_NAME. */
  lock_acquire (&cur->list_lock);

  tid = thread_create (file_name, PRI_DEFAULT, start_process, fn_copy);
  if (tid == TID_ERROR){
    palloc_free_page (fn_copy); 
  }
  else {

    sema_down (&cur->exec_sema);

    if (cur->load_reply){
      struct child_info *child = malloc (sizeof (struct child_info));
    
      child->tid = tid;         
      child->wait_called = false;    
      child->died = false;    
      sema_init (&child->wait_sema, 0);
      list_push_back (&cur->child_list, &child->child_elem);
    }
    else {
      sema_down (&cur->exec_sema);
      tid = TID_ERROR;
    }
  } 
  
  lock_release (&cur->list_lock);
  return tid;  
}

/* A thread function that loads a user process and starts it
   running. */
static void
start_process (void *file_name_)
{
  char *file_name = file_name_;
  struct intr_frame if_;
  bool success;
  struct thread *cur = thread_current ();

  /* Initialize interrupt frame and load executable. */
  memset (&if_, 0, sizeof if_);
  if_.gs = if_.fs = if_.es = if_.ds = if_.ss = SEL_UDSEG;
  if_.cs = SEL_UCSEG;
  if_.eflags = FLAG_IF | FLAG_MBS;
  
  lock_acquire (&filesys_lock);
  success = load (file_name, &if_.eip, &if_.esp); 
  lock_release (&filesys_lock);
  
  cur->parent->load_reply = success;
  cur->load_success = success;
  sema_up (&cur->parent->exec_sema);

  /* If load failed, quit. */
  palloc_free_page (file_name);
  if (!success) {
    cur->exit_status = -1;
    thread_exit ();
  }
 
  /* Start the user process by simulating a return from an
     interrupt, implemented by intr_exit (in
     threads/intr-stubs.S).  Because intr_exit takes all of its
     arguments on the stack in the form of a `struct intr_frame',
     we just point the stack pointer (%esp) to our stack frame
     and jump to it. */
  asm volatile ("movl %0, %%esp; jmp intr_exit" : : "g" (&if_) : "memory");
  NOT_REACHED ();
}

/* Waits for thread TID to die and returns its exit status.  If
   it was terminated by the kernel (i.e. killed due to an
   exception), returns -1.  If TID is invalid or if it was not a
   child of the calling process, or if process_wait() has already
   been successfully called for the given TID, returns -1
   immediately, without waiting.

   This function will be implemented in problem 2-2.  For now, it
   does nothing. */
int
process_wait (tid_t child_tid) 
{
  int exitStatus = -1;
  struct thread *cur = thread_current ();
  struct list_elem *e;
  struct list *c_list;

  lock_acquire (&cur->list_lock);
  c_list = &cur->child_list;

  e = list_begin (c_list);
  while (e != list_end (c_list)){

    struct child_info *fi = list_entry (e, struct child_info, child_elem);
    if (fi->tid == child_tid){

      if (!fi->wait_called){
               
        if (!fi->died){
          
          lock_release (&cur->list_lock);
          sema_down (&fi->wait_sema);
          lock_acquire (&cur->list_lock);
        }
  
        fi->wait_called = true;
        exitStatus = fi->exit_status;
      } 

      break;
    }

    e = list_next (e);
  }

  lock_release (&cur->list_lock);
  return exitStatus;
}

static void free_resource (struct thread *cur)
{
  struct list *fd_l;
  struct list_elem *e;
  struct hash_elem *he;
  struct hash_iterator i;
  struct hash *h = &cur->page_table;
  uint32_t *pd;

  //free page
  lock_acquire (&frame_lock);

  hash_first (&i, h);

  while (hash_size (h) > 0)
  {
    hash_first (&i, h);
    he = hash_next (&i);

    struct page *p = hash_entry (he, struct page, page_elem);

    if (p->in_swap){
    
      swap_free (false, NULL, p->swap_index);
    }
    else if (p->in_file) {
      
      /*after implementing mmap */
    }
    else 
      frame_free (p->frame_index);

    hash_delete (h, he);
  }
 
  pd = cur->pagedir;
  if (pd != NULL) 
    {
      /* Correct ordering here is crucial.  We must set
         cur->pagedir to NULL before switching page directories,
         so that a timer interrupt can't switch back to the
         process page directory.  We must activate the base page
         directory before destroying the process's page
         directory, or our active page directory will be one
         that's been freed (and cleared). */
      cur->pagedir = NULL;
      pagedir_activate (NULL);
      pagedir_destroy (pd);
    }
 
  lock_release (&frame_lock);
  
  //close all file
  fd_l = &cur->fd_list;

  while (list_size (fd_l) > 0){

    e = list_pop_front (fd_l);
    struct fd *fd_to_close = list_entry (e, struct fd, fd_elem);
    
    lock_acquire (&filesys_lock);
    file_close (fd_to_close->f);
    lock_release (&filesys_lock);

    free (fd_to_close);
  }

}

/* Free the current process's resources. */
void
process_exit (void)
{
  struct thread *cur = thread_current ();
  struct list_elem *e;
  struct list *c_list;

  /* Destroy the current process's page directory and switch back
     to the kernel-only page directory. */

  //CLOSE executable 
  if (!lock_held_by_current_thread (&filesys_lock))
    lock_acquire (&filesys_lock);
 
  file_close (cur->executable);
  lock_release (&filesys_lock);

  //free resource
  free_resource (cur);

  //자식 처리
  lock_acquire (&cur->list_lock);
  c_list = &cur->child_list;
  e = list_begin (c_list);

  while (e != list_end (c_list)){

    struct child_info *c_info = list_entry (e, struct child_info, child_elem);
    if (!c_info->died){   
      
      lock_release (&cur->list_lock);
      sema_down (&c_info->wait_sema);
      lock_acquire (&cur->list_lock);
    }
    
    list_pop_front (c_list);
    free (c_info);
    e = list_begin(c_list);
  }

  lock_release (&cur->list_lock);

  printf("%s: exit(%d)\n", cur->user_file, cur->exit_status);
  free(cur->user_file);

  //부모 바꾸기
  if (cur->tid != 1 && cur->tid != 2){
    
    if (!cur->load_success)
      sema_up (&cur->parent->exec_sema);

    lock_acquire (&cur->parent->list_lock);
    c_list = &cur->parent->child_list;

		for (e = list_begin (c_list); e != list_end (c_list); e = list_next (e)){
		
      struct child_info *c_info = list_entry (e, struct child_info, child_elem);
      if (c_info->tid == cur->tid){
 
        c_info->exit_status = cur->exit_status;
        c_info->died = true;
        sema_up (&c_info->wait_sema);
        break;
    	}
		}

    lock_release (&cur->parent->list_lock);
	}
}

/* Sets up the CPU for running user code in the current
   thread.
   This function is called on every context switch. */
void
process_activate (void)
{
  struct thread *t = thread_current ();

  /* Activate thread's page tables. */
  pagedir_activate (t->pagedir);

  /* Set thread's kernel stack for use in processing
     interrupts. */
  tss_update ();
}

/* We load ELF binaries.  The following definitions are taken
   from the ELF specification, [ELF1], more-or-less verbatim.  */

/* ELF types.  See [ELF1] 1-2. */
typedef uint32_t Elf32_Word, Elf32_Addr, Elf32_Off;
typedef uint16_t Elf32_Half;

/* For use with ELF types in printf(). */
#define PE32Wx PRIx32   /* Print Elf32_Word in hexadecimal. */
#define PE32Ax PRIx32   /* Print Elf32_Addr in hexadecimal. */
#define PE32Ox PRIx32   /* Print Elf32_Off in hexadecimal. */
#define PE32Hx PRIx16   /* Print Elf32_Half in hexadecimal. */

/* Executable header.  See [ELF1] 1-4 to 1-8.
   This appears at the very beginning of an ELF binary. */
struct Elf32_Ehdr
  {
    unsigned char e_ident[16];
    Elf32_Half    e_type;
    Elf32_Half    e_machine;
    Elf32_Word    e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    Elf32_Word    e_flags;
    Elf32_Half    e_ehsize;
    Elf32_Half    e_phentsize;
    Elf32_Half    e_phnum;
    Elf32_Half    e_shentsize;
    Elf32_Half    e_shnum;
    Elf32_Half    e_shstrndx;
  };

/* Program header.  See [ELF1] 2-2 to 2-4.
   There are e_phnum of these, starting at file offset e_phoff
   (see [ELF1] 1-6). */
struct Elf32_Phdr
  {
    Elf32_Word p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Elf32_Word p_filesz;
    Elf32_Word p_memsz;
    Elf32_Word p_flags;
    Elf32_Word p_align;
  };

/* Values for p_type.  See [ELF1] 2-3. */
#define PT_NULL    0            /* Ignore. */
#define PT_LOAD    1            /* Loadable segment. */
#define PT_DYNAMIC 2            /* Dynamic linking info. */
#define PT_INTERP  3            /* Name of dynamic loader. */
#define PT_NOTE    4            /* Auxiliary info. */
#define PT_SHLIB   5            /* Reserved. */
#define PT_PHDR    6            /* Program header table. */
#define PT_STACK   0x6474e551   /* Stack segment. */

/* Flags for p_flags.  See [ELF3] 2-3 and 2-4. */
#define PF_X 1          /* Executable. */
#define PF_W 2          /* Writable. */
#define PF_R 4          /* Readable. */

static bool setup_stack (void **esp, const char *file_name_);
static bool validate_segment (const struct Elf32_Phdr *, struct file *);
static bool load_segment (struct file *file, off_t ofs, uint8_t *upage,
                          uint32_t read_bytes, uint32_t zero_bytes,
                          bool writable);

/* Loads an ELF executable from FILE_NAME into the current thread.
   Stores the executable's entry point into *EIP
   and its initial stack pointer into *ESP.
   Returns true if successful, false otherwise. */
bool
load (const char *file_name, void (**eip) (void), void **esp) 
{
  struct thread *t = thread_current ();
  struct Elf32_Ehdr ehdr;
  struct file *file = NULL;
  off_t file_ofs;
  bool success = false;
  int i, file_name_size;
  char *first_space;

  /* Allocate and activate page directory. */
  t->pagedir = pagedir_create ();
  if (t->pagedir == NULL) 
    goto done;
  process_activate ();

  /* Open executable file. */
  first_space = strchr (file_name, ' ');

  if(first_space == NULL)
    file_name_size = strlen(file_name);
  else
    file_name_size = (int)(first_space - file_name);

  t->user_file = malloc (file_name_size + 1);
  strlcpy (t->user_file, file_name, file_name_size + 1);
  file = filesys_open (t->user_file);
  t->executable = file;

  if (file == NULL) 
    {
      printf ("load: %s: open failed\n", t->user_file);
      goto done; 
    }

  file_deny_write (file); //deny write to executable
  
  /* Read and verify executable header. */
  if (file_read (file, &ehdr, sizeof ehdr) != sizeof ehdr
      || memcmp (ehdr.e_ident, "\177ELF\1\1\1", 7)
      || ehdr.e_type != 2
      || ehdr.e_machine != 3
      || ehdr.e_version != 1
      || ehdr.e_phentsize != sizeof (struct Elf32_Phdr)
      || ehdr.e_phnum > 1024) 
    {
      printf ("load: %s: error loading executable\n", t->user_file);
      goto done; 
    }

  /* Read program headers. */
  file_ofs = ehdr.e_phoff;
  for (i = 0; i < ehdr.e_phnum; i++) 
    {
      struct Elf32_Phdr phdr;

      if (file_ofs < 0 || file_ofs > file_length (file))
        goto done;
      file_seek (file, file_ofs);

      if (file_read (file, &phdr, sizeof phdr) != sizeof phdr)
        goto done;
      file_ofs += sizeof phdr;
      switch (phdr.p_type) 
        {
        case PT_NULL:
        case PT_NOTE:
        case PT_PHDR:
        case PT_STACK:
        default:
          /* Ignore this segment. */
          break;
        case PT_DYNAMIC:
        case PT_INTERP:
        case PT_SHLIB:
          goto done;
        case PT_LOAD:
          if (validate_segment (&phdr, file)) 
            {
              bool writable = (phdr.p_flags & PF_W) != 0;
              uint32_t file_page = phdr.p_offset & ~PGMASK;
              uint32_t mem_page = phdr.p_vaddr & ~PGMASK;
              uint32_t page_offset = phdr.p_vaddr & PGMASK;
              uint32_t read_bytes, zero_bytes;
              if (phdr.p_filesz > 0)
                {
                  /* Normal segment.
                     Read initial part from disk and zero the rest. */
                  read_bytes = page_offset + phdr.p_filesz;
                  zero_bytes = (ROUND_UP (page_offset + phdr.p_memsz, PGSIZE)
                                - read_bytes);
                }
              else 
                {
                  /* Entirely zero.
                     Don't read anything from disk. */
                  read_bytes = 0;
                  zero_bytes = ROUND_UP (page_offset + phdr.p_memsz, PGSIZE);
                }
              if (!load_segment (file, file_page, (void *) mem_page,
                                 read_bytes, zero_bytes, writable))
                goto done;
            }
          else
            goto done;
          break;
        }
    }

  /* Set up stack. */
  if (!setup_stack (esp, file_name))
    goto done;

  /* Start address. */
  *eip = (void (*) (void)) ehdr.e_entry;

  success = true;

 done:
  /* We arrive here whether the load is successful or not. */
  return success;
}

/* load() helpers. */

static bool install_page (void *upage, void *kpage, bool writable);

/* Checks whether PHDR describes a valid, loadable segment in
   FILE and returns true if so, false otherwise. */
static bool
validate_segment (const struct Elf32_Phdr *phdr, struct file *file) 
{
  /* p_offset and p_vaddr must have the same page offset. */
  if ((phdr->p_offset & PGMASK) != (phdr->p_vaddr & PGMASK)) 
    return false; 

  /* p_offset must point within FILE. */
  if (phdr->p_offset > (Elf32_Off) file_length (file)) 
    return false;

  /* p_memsz must be at least as big as p_filesz. */
  if (phdr->p_memsz < phdr->p_filesz) 
    return false; 

  /* The segment must not be empty. */
  if (phdr->p_memsz == 0)
    return false;
  
  /* The virtual memory region must both start and end within the
     user address space range. */
  if (!is_user_vaddr ((void *) phdr->p_vaddr))
    return false;
  if (!is_user_vaddr ((void *) (phdr->p_vaddr + phdr->p_memsz)))
    return false;

  /* The region cannot "wrap around" across the kernel virtual
     address space. */
  if (phdr->p_vaddr + phdr->p_memsz < phdr->p_vaddr)
    return false;

  /* Disallow mapping page 0.
     Not only is it a bad idea to map page 0, but if we allowed
     it then user code that passed a null pointer to system calls
     could quite likely panic the kernel by way of null pointer
     assertions in memcpy(), etc. */
  if (phdr->p_vaddr < PGSIZE)
    return false;

  /* It's okay. */
  return true;
}

/* Loads a segment starting at offset OFS in FILE at address
   UPAGE.  In total, READ_BYTES + ZERO_BYTES bytes of virtual
   memory are initialized, as follows:

        - READ_BYTES bytes at UPAGE must be read from FILE
          starting at offset OFS.

        - ZERO_BYTES bytes at UPAGE + READ_BYTES must be zeroed.

   The pages initialized by this function must be writable by the
   user process if WRITABLE is true, read-only otherwise.

   Return true if successful, false if a memory allocation error
   or disk read error occurs. */
static bool
load_segment (struct file *file, off_t ofs, uint8_t *upage,
              uint32_t read_bytes, uint32_t zero_bytes, bool writable) 
{
  ASSERT ((read_bytes + zero_bytes) % PGSIZE == 0);
  ASSERT (pg_ofs (upage) == 0);
  ASSERT (ofs % PGSIZE == 0);

  struct thread *t = thread_current ();

  while (read_bytes > 0 || zero_bytes > 0) 
    {
      /* Calculate how to fill this page.
         We will read PAGE_READ_BYTES bytes from FILE
         and zero the final PAGE_ZERO_BYTES bytes. */
      size_t page_read_bytes = read_bytes < PGSIZE ? read_bytes : PGSIZE;
      size_t page_zero_bytes = PGSIZE - page_read_bytes;

      /* Get a page entry for supplemental page table */
      struct page *p = malloc (sizeof (struct page));
      if (p == NULL)
        return false;
     
      /* Setting page entry*/
      p->pd = thread_current ()->pagedir;
      p->upage = upage;
      p->kpage = NULL;
      p->in_file = true;
      p->in_swap = false;
      p->frame_index = NULL;
      p->writable = writable;
      p->file_ofs = ofs;
      p->read_bytes = page_read_bytes;
      p->zero_bytes = page_zero_bytes;
      p->page_file = file;
      
      /* add to supplemental page table */
      page_insert (&t->page_table, p);
   

      //printf ("upage %x\n", upage);
      /* Advance. */
      read_bytes -= page_read_bytes;
      zero_bytes -= page_zero_bytes;
      upage += PGSIZE;
      ofs += page_read_bytes;   
    }
  return true;
}

/* Create a minimal stack by mapping a zeroed page at the top of
   user virtual memory. */
static bool
setup_stack (void **esp, const char *file_name_) 
{

  struct frame *earned_frame;
  uint8_t *kpage, *upage;
  bool success = false;
  int fname_size = strlen(file_name_), arg_c;
  char *file_name = malloc(fname_size + 1);
  struct thread *t = thread_current ();
  struct page *p;

  earned_frame = frame_alloc(PAL_ZERO);//palloc_get_page (PAL_USER | PAL_ZERO);
  kpage = earned_frame->kpage;
  upage = ((uint8_t *) PHYS_BASE) - PGSIZE;

  if (kpage != NULL) 
    {
      success = install_page (upage, kpage, true);
      if (success){
        
        char *token, *save_ptr;
        int index = 0, i;
        *esp = PHYS_BASE;
        memcpy (file_name, file_name_, fname_size + 1);        

        // get argc 
        for(token = strtok_r (file_name, " ", &save_ptr); token != NULL;
            token = strtok_r (NULL, " ", &save_ptr))
          index++;
      
        arg_c = index;
        char *arg_v[arg_c];
        index = 0;
        memcpy (file_name, file_name_, fname_size + 1);
        
        // push arguments and fill in the argv 
        for(token = strtok_r (file_name, " ", &save_ptr); token != NULL;
            token = strtok_r (NULL, " ", &save_ptr)){
           
          int token_size = strlen (token);
          *esp = (char *)*esp - token_size - 1;
          memcpy (*esp, token, token_size + 1); 
          arg_v[index] = *esp;
          index ++;

        }

        // word-align 
        *esp = (void *)((unsigned long)*esp >> 2 << 2);

        // argv[argc] = null 
        *esp = (char *)*esp - 4;

        // push argv element 
        for(i = arg_c-1; i >=0; i--){
          *esp = (char *)*esp - 4;
          **(char ***)esp = arg_v[i]; 
        }
  
        // push argv 
        *esp = (char *)*esp - 4;
        **(char ***)esp =(char *)*esp + 4; 

        // push argc 
        *esp = (char *)*esp - 4;
        **(int **)esp = arg_c;

        // push return address 
        *esp = (char *)*esp - 4;  
      }
      else
        palloc_free_page (kpage);
    }

  //hex_dump (*esp, *esp, 0xc0000000 - (uint32_t)*esp, true);
  free(file_name);
  pagedir_set_dirty (t->pagedir, upage, true);
  
  p = malloc (sizeof (struct page));
  p->pd = t->pagedir;
  p->upage = upage;
  p->kpage = kpage;
  p->in_file = false;
  p->in_swap = false;
  p->writable = true;
  p->frame_index = earned_frame;

  page_insert (&t->page_table, p);

  t->stack_end = upage;
  earned_frame->upage = upage;
  earned_frame->frame_thread = t;
  earned_frame->pinned = false;
  return success; 
}

/* Adds a mapping from user virtual address UPAGE to kernel
   virtual address KPAGE to the page table.
   If WRITABLE is true, the user process may modify the page;
   otherwise, it is read-only.
   UPAGE must not already be mapped.
   KPAGE should probably be a page obtained from the user pool
   with palloc_get_page().
   Returns true on success, false if UPAGE is already mapped or
   if memory allocation fails. */
static bool
install_page (void *upage, void *kpage, bool writable)
{
  struct thread *t = thread_current ();

  /* Verify that there's not already a page at that virtual
     address, then map our page there. */
  return (pagedir_get_page (t->pagedir, upage) == NULL
          && pagedir_set_page (t->pagedir, upage, kpage, writable));
}
