#ifndef VM_PAGE_H
#define VM_PAGE_H
#include <hash.h>
#include <stdio.h>
#include <list.h>

struct page
  {
    struct hash_elem page_elem;
    uint32_t *pd;
    void *upage, *kpage;
    bool in_file, in_swap, writable;
    struct list_elem *frame_index;
    uint32_t file_ops;
    uint32_t read_byte, zaro_byte;
  };

unsigned page_hash (const struct hash_elem *, void *);
bool page_less (const struct hash_elem *, const struct hash_elem *, void *);
void page_init (struct hash);
struct page *page_search (struct hash, void *);
void page_insert (struct hash, struct page *);
    
#endif
