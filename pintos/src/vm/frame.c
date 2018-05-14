#include "vm/frame.h"
#include "vm/page.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "threads/malloc.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "userprog/syscall.h"
#include <debug.h>

static struct list frame_table;
static struct list_elem *hand;
static struct lock frame_lock;

void frame_init (void){
  
  list_init (&frame_table);
  lock_init (&frame_lock);
  hand = list_end (&frame_table);
}

struct frame *frame_evict (void){

  struct frame *f;
  struct thread *t;
  struct page *p;
  lock_acquire (&frame_lock);

  while (true){
    
    if (hand == list_end (&frame_table))
      hand = list_begin (&frame_table);

    f = list_entry (hand, struct frame, frame_elem);
    t = f->frame_thread;

    if (pagedir_is_accessed (t->pagedir, f->upage)){

      pagedir_set_accessed (t->pagedir, f->upage, 0);
      hand = list_next (hand);
    }
    else
      break;
  }
  
  /*
     implement 2.B.iii
     implement 2.B.iv
  */
  lock_acquire (&t->page_lock);
  pagedir_clear_page (t->pagedir, f->upage);

  p = page_search (&t->page_table, f->upage);
  p->kpage = NULL;
  p->frame_index = NULL;

  if (pagedir_is_dirty (t->pagedir, f->upage)){
  
    if (f->mmapped){

      lock_acquire (&filesys_lock);
      file_seek (f->frame_file, f->file_ofs);
      file_write (f->frame_file, f->kpage, PGSIZE);
      lock_release (&filesys_lock);

      p->in_file = true;
      p->in_swap = false;
    }
    else{
      //write frame to swap partition

      p->in_file = false;
      p->in_swap = true;
    }
  }
  else{

    p->in_file = true;
    p->in_swap = false;
  }

  lock_release (&t->page_lock);

  f->pinned = true;
  hand = list_next (hand);
  lock_release (&frame_lock);

  return f;
}

struct frame *frame_alloc (enum palloc_flags flags){
  
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

    lock_acquire (&frame_lock);
    list_push_back (&frame_table, &f->frame_elem);
    lock_release (&frame_lock);

  }

  return f;
}

void frame_free (struct list_elem *e){

  lock_acquire (&frame_lock);
  
  if (hand == e)
    hand = list_next (hand);

  list_remove (e);
  lock_release (&frame_lock);
}

  
  
