#ifndef VM_CACHE_H
#define VM_CACHE_H

#include <list.h>
#include <stdbool.h>
#include "devices/block.h"
#include "threads/synch.h"

struct cache_entry
{
  bool dirty, empty;
  int64_t ticks;
  struct list_elem cache_elem;
  void *memory;
  block_sector_t sector;
  struct lock cache_lock;

};

void cache_init (void);
bool cache_search (block_sector_t, struct cache_entry **);
void cache_read (block_sector_t, int, int, void *);
void cache_write (block_sector_t, int, int, void *);
void write_behind (void *);
void cache_destroy (void);
#endif
