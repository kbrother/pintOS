#include "vm/page.h"
#include "threads/synch.h"

unsigned
page_hash (const struct hash_elem *p_, void *aux UNUSED){

  const struct page *p = hash_entry (p_, struct page, page_elem);
  return hash_bytes (&p->upage, sizeof p->upage);

}

bool
page_less (const struct hash_elem *a_, const struct hash_elem *b_,
    void *aux UNUSED)
{
  const struct page *a = hash_entry (a_, struct page, page_elem);
  const struct page *b = hash_entry (b_, struct page, page_elem);

  return a->upage < b->upage;
}

void page_init (struct hash *page_table){

  hash_init (page_table, page_hash, page_less, NULL);
}

struct page *page_search (struct thread *t, void *address)
{
  struct page p;
  struct hash_elem *e;
  struct hash *page_table = &t->page_table;
  p.upage = address;

  lock_acquire (&t->page_lock);
  e = hash_find (page_table, &p.page_elem);
  lock_release (&t->page_lock);

  return e != NULL ? hash_entry (e, struct page, page_elem) : NULL;
}

void page_insert (struct thread *t, struct page *p)
{
  struct hash *page_table = &t->page_table;

  lock_acquire (&t->page_lock);
  hash_insert (page_table, &p->page_elem);
  lock_release (&t->page_lock);

}

void page_delete (struct thread *t, struct page *p)
{
  struct hash *page_table = &t->page_table;

  lock_acquire (&t->page_lock);
  hash_delete (page_table, &p->page_elem);
  lock_release (&t->page_lock);

  free (p);
}

