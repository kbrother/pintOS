#include "filesys/cache.h"
#include <stdio.h>
#include <string.h>
#include "threads/thread.h"
#include "threads/malloc.h"
#include "devices/timer.h"
#include "filesys/filesys.h"

static struct list cache;

void cache_init (void)
{
  int i;

  list_init (&cache);

  for (i = 0; i < 64; i++)
  {
    struct cache_entry *entry = malloc (sizeof (struct cache_entry));
    entry->dirty = false;
    entry->empty = true;
    entry->ticks = -1;
    entry->sector = -1;
    entry->memory = malloc (BLOCK_SECTOR_SIZE);
    lock_init (&entry->cache_lock);
    list_push_back (&cache, &entry->cache_elem);
  }
}

static void release_prev (struct cache_entry *entry)
{
  if (entry != NULL)
    lock_release (&entry->cache_lock);
}

bool cache_search (block_sector_t sector, struct cache_entry **entry)
{
  struct list_elem *e = list_begin (&cache);
  int64_t ticks;
  *entry = NULL;
  bool empty_found = false;
  struct cache_entry *ce;

  while (e != list_end (&cache))
  {
    ce = list_entry (e, struct cache_entry, cache_elem);

    lock_acquire (&ce->cache_lock);

    if (ce->sector == sector)
    {
      release_prev (*entry); 
      *entry = ce;
      ce->ticks = timer_ticks ();
      return true;
    }

    if (empty_found)
    {
      lock_release (&ce->cache_lock);
      e = list_next (e);
      continue;
    }

    if (ce->empty)
    {
      release_prev (*entry);
      *entry = ce;
      e = list_next (e);
      empty_found = true;
      continue ;
    }

    if (e == list_begin (&cache) ||
        ticks > ce->ticks)
    {
      release_prev (*entry);
      ticks = ce->ticks;
      *entry = ce;
    }
    else
      lock_release (&ce->cache_lock);

    e = list_next (e);
  }

  ce = *entry;
  ce->ticks = timer_ticks ();

  return false;
}


static void cache_evict (block_sector_t sector, struct cache_entry *victim)
{
  if (victim->dirty)
    block_write (fs_device, victim->sector, victim->memory);

  block_read (fs_device, sector, victim->memory);

  victim->sector = sector;
  victim->empty = false;
}

static void read_ahead (void *sector_)
{
  block_sector_t sector = *(block_sector_t *)sector_;
  struct cache_entry *ret;

  if (!cache_search (sector, &ret))
  {
    cache_evict (sector, ret);
    ret->dirty = false;
  }

  lock_release (&ret->cache_lock);
  free (sector_);
}

void cache_read (block_sector_t sector, int start, int size, void *buffer)
{
  struct cache_entry *ret;;
  uint32_t *sec = malloc (4);
  tid_t tid;

  if (!cache_search (sector, &ret))
  {
    cache_evict (sector, ret);
    ret->dirty = false;
  }

  memcpy (buffer, (char *)ret->memory + start, size);
  lock_release (&ret->cache_lock);

  *sec = sector + 1;
  tid = thread_create ("read_ahead", PRI_DEFAULT, read_ahead, sec);

  if (tid == TID_ERROR)
    free (sec);   
}

void cache_write (block_sector_t sector, int start, int size, void *buffer)
{
  struct cache_entry *ret;

  if (!cache_search (sector, &ret))
    cache_evict (sector, ret);

  ret->dirty = true;
  memcpy ((char *)ret->memory + start, buffer, size);
  lock_release (&ret->cache_lock);
}

void write_behind (void *aux UNUSED)
{
  struct list_elem *e;
  struct cache_entry *ce;

  for (e = list_begin (&cache); e != list_end (&cache); e = list_next (e))
  {
    ce = list_entry (e, struct cache_entry, cache_elem);  

    if (ce->dirty)
      block_write (fs_device, ce->sector, ce->memory);      
    
    ce->dirty = false;
  }
}

void cache_destroy (void)
{
  while (list_size (&cache) > 0)
  {
    struct list_elem *e = list_pop_front (&cache);
    struct cache_entry *ce = list_entry (e, struct cache_entry, cache_elem);

    free (ce->memory);
    free (ce);
  }

}




