#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "userprog/pagedir.h"
#include "threads/vaddr.h"
#include "threads/malloc.h"
#include "devices/shutdown.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static bool valid_memory(void *uaddr){

  uint32_t *pd = thread_current()->pagedir;

  if (uaddr == NULL)
    return false;

  if (!is_user_vaddr (uaddr))
    return false;

  if (pagedir_get_page (pd, uaddr) == NULL)
    return false;

  return true;
}

static void get_arg (uint32_t **syscall_arg, int arg_num, void *esp){

  uint32_t *arg_pointer = (uint32_t *)((char *)esp + 4);
  *syscall_arg = malloc (4 * arg_num);
  int i;

  for (i = 0; i < arg_num; i++){

    if (!valid_memory (arg_pointer)){
      free(*syscall_arg);
      thread_exit();
    }

    (*syscall_arg)[i] = *arg_pointer;
    arg_pointer += 1;
  }
}

static void sys_halt (void){
 shutdown_power_off(); 
}

static void sys_exit (uint32_t *syscall_arg){

  int status = syscall_arg[0];
  thread_current ()->exit_status = status;
  printf("sys_exit\n");
  thread_exit ();
}

static void sys_exec (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){
  
  printf("sys_Exec!\n");
  thread_exit ();
    
}

static void sys_wait (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){

  printf("sys_wait!\n");
  thread_exit ();
}

static void sys_create (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){

  printf("sys_create!\n");
  thread_exit ();
}

static void sys_remove (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){

  printf("system_remove!\n");
  thread_exit ();
}

static void sys_open (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){

  printf("system_open!\n");
  thread_exit ();
}
  
static void sys_filesize (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){
  
  printf("sys_filesize!\n");
  thread_exit ();
}

static void sys_read (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){

  printf("sys_read!\n");
  thread_exit ();
}

static void sys_write (uint32_t *syscall_arg, uint32_t eax UNUSED){
  
  int fd = syscall_arg[0];
  void *buffer = (void *)syscall_arg[1];
  unsigned size = syscall_arg[2];

  if (fd == 1){

    while (size > 0){

      int print_size = size > 100 ? 100 : size;
      putbuf ((char *)buffer, print_size);
      size -= print_size;
    }
  }
  else{
    free(syscall_arg);
    thread_exit ();
  }
}

static void sys_seek (uint32_t *syscall_arg UNUSED){

  printf("sys_seek!\n");
  thread_exit ();
}

static void sys_tell (uint32_t *syscall_arg UNUSED, uint32_t eax UNUSED){

  printf("sys_tell!\n");
  thread_exit ();

}

static void sys_close (uint32_t *syscall_arg UNUSED){

  printf("sys_close!\n");
  thread_exit ();
}

static void
syscall_handler (struct intr_frame *f) 
{  
  if (!valid_memory (f->esp))
    thread_exit();

  int syscall_num = *(int *)f->esp;
  uint32_t *syscall_arg;

  switch (syscall_num){
    
    case SYS_HALT :
      sys_halt();
      break;
    
    case SYS_EXIT :
      get_arg (&syscall_arg, 1, f->esp);
      sys_exit(syscall_arg);
      break;

    case SYS_EXEC :
      get_arg (&syscall_arg, 1, f->esp);
      sys_exec (syscall_arg, f->eax);
      break;

    case SYS_WAIT :
      get_arg (&syscall_arg, 1, f->esp);
      sys_wait (syscall_arg, f->eax);
      break;

    case SYS_CREATE :
      get_arg (&syscall_arg, 2, f->esp);
      sys_create (syscall_arg, f->eax);
      break;
  
    case SYS_REMOVE :
      get_arg (&syscall_arg, 1, f->esp);
      sys_remove (syscall_arg, f->eax);
      break;
    
    case SYS_OPEN :
      get_arg (&syscall_arg, 1, f->esp);
      sys_remove (syscall_arg, f->eax);
      break;

    case SYS_FILESIZE :
      get_arg (&syscall_arg, 1, f->esp);
      sys_filesize (syscall_arg, f->eax);
      break;

    case SYS_READ :
      get_arg (&syscall_arg, 3, f->esp);
      sys_read (syscall_arg, f->eax);
      break;

    case SYS_WRITE :
      get_arg (&syscall_arg, 3, f->esp);
      sys_write (syscall_arg, f->eax);
      break;
    
    case SYS_SEEK :
      get_arg (&syscall_arg, 2, f->esp);
      sys_seek (syscall_arg);
      break;

    case SYS_TELL :
      get_arg (&syscall_arg, 1, f->esp);
      sys_tell (syscall_arg, f->eax);
      break;

    case SYS_CLOSE :
      get_arg (&syscall_arg, 1, f->esp);
      sys_close (syscall_arg);
      break;

    default :
      thread_exit ();
  }

  free(syscall_arg);
}


