#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <hash.h>
#include <list.h>
#include "threads/palloc.h"
#include "filesys/file.h"

struct frame
  {
    struct thread *frame_thread;
    struct list_elem frame_elem;
    void *upage, *kpage;
    bool mmapped, pinned;
    uint32_t file_ofs;
    struct file *frame_file;
  };

void frame_init (void);
struct frame *frame_evict (void);
struct frame *frame_alloc (enum palloc_flags);
void frame_free (struct list_elem *);

#endif /* vm/frame.h */
