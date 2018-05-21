#include "vm/frame.h"
#include "vm/page.h"
#include "vm/swap.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "threads/malloc.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "userprog/syscall.h"
#include <debug.h>
#include <stdbool.h>

static struct list frame_table;
static struct list_elem *hand;
struct lock frame_lock;

void frame_init (void){
  
  list_init (&frame_table);
  lock_init (&frame_lock);
  hand = list_end (&frame_table);
}

struct frame *frame_evict (void){

  struct frame *f;
  struct thread *t;
  struct page *p;

  /* select victm */
  while (true){
    
    if (hand == list_end (&frame_table))
      hand = list_begin (&frame_table);

    ASSERT (t != NULL);
    f = list_entry (hand, struct frame, frame_elem);
    t = f->frame_thread;

    hand = list_next (hand);

    if (f->pinned)
      continue;

    if (pagedir_is_accessed (t->pagedir, f->upage)){
      
      pagedir_set_accessed (t->pagedir, f->upage, false);
      continue;

    }
    
    break;
  }
  
  f->pinned = true;

  /* update victim's page table */
  pagedir_clear_page (t->pagedir, f->upage);

  p = page_search (t, f->upage);
  p->kpage = NULL;
  p->frame_index  = NULL;

  if (pagedir_is_dirty (t->pagedir, f->upage)){
  
    if (f->mmapped){

      lock_acquire (&filesys_lock);
      file_seek (f->frame_file, f->file_ofs);
      file_write (f->frame_file, f->kpage, f->read_bytes);
      lock_release (&filesys_lock);

      p->in_file = true;
      p->in_swap = false;
    }
    else{
      //write frame to swap partition

      p->swap_index = swap_alloc (f->kpage);
      p->in_file = false;
      p->in_swap = true;
    }
  }
  else{

    p->in_file = true;
    p->in_swap = false;
  }

  return f;
}

struct frame *frame_alloc (enum palloc_flags flags){
 
  lock_acquire (&frame_lock);

  void *add = palloc_get_page (PAL_USER | flags);
  struct frame *f;

  if (add == NULL)
    f = frame_evict ();
  else
  {
    f = malloc (sizeof (struct frame));
    
    f->frame_thread = thread_current ();
    f->kpage = add;
    f->pinned = true;

    list_push_back (&frame_table, &f->frame_elem);
  }

  lock_release (&frame_lock);
  return f;
}

void frame_free (struct thread *t, struct frame *f){

  struct list_elem *e = &f->frame_elem;

  if (hand == e)
    hand = list_next (hand);

  pagedir_clear_page (t->pagedir, f->upage);
  palloc_free_page (f->kpage);

  list_remove (e);
  free (f);

}

bool frame_search_and_pin (int tid, void *upage, struct frame **frame_pt){

  lock_acquire (&frame_lock);
  struct list_elem *e = list_begin (&frame_table);
 
  while (e != list_end (&frame_table))
  {
    struct frame *f = list_entry (e, struct frame, frame_elem);
    if (f->frame_thread->tid == tid)
    {
      if (f->upage == upage)
      {
        f->pinned = true;
        *frame_pt = f;
        lock_release (&frame_lock);
        return true;
      }
    }

    e = list_next (e);
  }

  lock_release (&frame_lock);
  return false;
}
  
  
