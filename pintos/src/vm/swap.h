#ifndef VM_SWAP_H
#define VM_SWAP_H
#include "devices/block.h"
#include <stdbool.h>

void swap_init (void);
block_sector_t swap_alloc (void *);
void swap_free (bool, void *, block_sector_t);
void swap_destroy (void);

#endif
