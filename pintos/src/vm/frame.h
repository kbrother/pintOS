#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <hash.h>
#include <list.h>
#include <stdbool.h>
#include "threads/palloc.h"
#include "filesys/file.h"

extern struct lock frame_lock;
struct frame
  {
    struct thread *frame_thread;
    struct list_elem frame_elem;
    void *upage, *kpage;
    bool mmapped, pinned;
    uint32_t file_ofs, read_bytes;
    struct file *frame_file;
  };

void frame_init (void);
struct frame *frame_evict (void);
struct frame *frame_alloc (enum palloc_flags);
void frame_free (struct thread *, struct frame *);
bool frame_search_and_pin (int , void *, struct frame **);
#endif /* vm/frame.h */
