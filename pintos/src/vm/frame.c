#include "vm/frame.h"

static struct hash frame_table;

unsigned frame_hash (const struct hash_elem *f_, void *aux UNUSED){

  const struct frame *f = hash_entry (f_, struct frame, hash_elem);
  return hash_bytes (&f->kpage, sizeof f->kpage);
}

bool frame_less (const struct hash_elem *a_, const struct hash_elem *b_, void *aux UNUSED){

  const struct frame *a = hash_entry (a_, struct frame, hash_elem);
  const struct frame *b = hash_entry (b_, struct frame, hash_elem);

  return a->kpage < b->kpage;
}

void frame_init (void){
  
  hash_init (&frame_table, frame_hash, frame_less, NULL);
}
