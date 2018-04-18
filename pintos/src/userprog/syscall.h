#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include <list.h>
extern struct lock filesys_lock;
void syscall_init (void);
#endif /* userprog/syscall.h */
