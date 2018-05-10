#include "vm/frame.h"
#include "threads/synch.h"
#include "userprog/pagedir.h"
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
  lock_acquire (&frame_lock);

  while (true){
    
    if (hand == list_end (&frame_table))
      hand = list_begin (&frame_table);

    f = list_entry (hand, struct frame, frame_elem);

    if (pagedir_is_accessed (f->pd, f->upage)){

      pagedir_set_accessed (f->pd, f->upage, 0);
      hand = list_next (hand);
    }
    else
      break;
  }

  /*
     implement 2.B.iii
     implement 2.B.iv
  */

  f->pinned = true;
  hand = list_next (hand);
  lock_release (&frame_lock);

  return f;
}

void *frame_alloc (enum palloc_flags flags){
  
  void *add = palloc_get_page (PAL_USER | PAL_ASSERT | flags); //edit after adding frame eviction

  // implement 2.D.ii

  return add;
}

void frame_free (void){

  lock_acquire (&frame_lock);

  while (!list_empty (&frame_table)){

    struct list_elem *e = list_pop_front (&frame_table);
    free (list_entry (e, struct frame, frame_elem));
  }

  lock_release (&frame_lock);
}

  
  
