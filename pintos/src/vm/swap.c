#include "vm/swap.h"
#include <bitmap.h>
#include "threads/synch.h"
#include <debug.h>

static struct bitmap *swap_table;
static struct lock swap_lock;
static struct block *swap_block;
static uint32_t swap_len;

void swap_init (void)
{
  lock_init (&swap_lock);
  swap_block = block_get_role (BLOCK_SWAP);
  
  if (swap_block != NULL){
  
    swap_len = block_size (swap_block);
    swap_table = bitmap_create (swap_len);
  }
}

block_sector_t swap_alloc (void *buffer)
{
  block_sector_t index;
  int i;

  lock_acquire (&swap_lock);
  index = bitmap_scan (swap_table, 0, 8, false);

  for (i = 0; i < 8; i++){

    block_write (swap_block, index, buffer);
    bitmap_mark (swap_table, index);

    index += 1;
    buffer = (char *)buffer + BLOCK_SECTOR_SIZE;
  }

  lock_release (&swap_lock);
  index -= 8;

  return index;
}

void swap_free (bool read_back, void *buffer, block_sector_t index)
{
  uint32_t i;
  lock_acquire (&swap_lock);
  
  for (i = 0; i < 8; i++){
    bitmap_reset (swap_table, index);

    if (read_back){
      block_read (swap_block, index, buffer);
      buffer = (char *)buffer + BLOCK_SECTOR_SIZE;
    }

    index += 1;
  }

  lock_release (&swap_lock);
}

void swap_destroy (void)
{
  bitmap_destroy (swap_table);
}









