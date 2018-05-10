#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <hash.h>
#include <list.h>
#include "threads/palloc.h"

struct frame
  {
    struct thread *frame_thread;
    struct list_elem frame_elem;
    uint32_t *pd;
    void *upage, *kpage;
    bool mmapped;
    bool pinned;
  };

void frame_init (void);
struct frame *frame_evict (void);
void *frame_alloc (enum palloc_flags);
void frame_free (void);

#endif /* vm/frame.h */
