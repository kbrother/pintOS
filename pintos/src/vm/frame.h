#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <hash.h>
#include <debug.h>

struct frame
  {
    struct hash_elem hash_elem;
    uint32_t *pd;
    void *upage, *kpage;
    bool mmapped;
  };

unsigned frame_hash (const struct hash_elem *p_, void *aux UNUSED);
bool frame_less (const struct hash_elem *a_, const struct hash_elem *b_, void *aux UNUSED);
void frame_init (void);
#endif /* vm/frame.h */
