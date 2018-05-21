#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include <list.h>
#include "threads/thread.h"
#include "filesys/file.h"

extern struct lock filesys_lock;
void syscall_init (void);
void unmap (struct thread *, struct mfd *);
#endif /* userprog/syscall.h */
