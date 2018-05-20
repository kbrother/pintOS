#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include <string.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"
#include "userprog/exception.h"
#include "vm/frame.h"
#include "vm/page.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "devices/input.h"
#include "devices/shutdown.h"

struct lock filesys_lock;
static void syscall_handler (struct intr_frame *);
static int fd_index;

static struct fd* search_by_fd (int fd){
  
  struct list_elem *e;
  struct list *fd_list = &thread_current()->fd_list;

  e = list_begin (fd_list);
  while (e != list_end (fd_list)){

    struct fd *temp = list_entry (e, struct fd, fd_elem);
    if (temp->fd_num == fd)
      return temp;

    e = list_next (e);
  }

  return NULL;
}

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  lock_init (&filesys_lock);
  fd_index = 2;
}

static bool valid_memory(void *uaddr){

  if (uaddr == NULL)
    return false;

  if (!is_user_vaddr (uaddr))
    return false;

  return true;
}


static bool vm_with_pinning (void *uaddr, struct frame **frame_pt){

  struct thread *t = thread_current ();
  void *upage = pg_round_down (uaddr);
  struct page *fp_info;

  if (uaddr == NULL)
    return false;

  if (!is_user_vaddr (uaddr))
    return false;

  if (!frame_search_and_pin (t->tid, upage, frame_pt))
  { 
    fp_info = page_search (&t->page_table, upage);

    if (fp_info == NULL)
      return false;

    *frame_pt = page_claim_and_set (t, fp_info);
  }

  return true;
}

static void get_arg (uint32_t **syscall_arg, int arg_num, void *esp){

  uint32_t *arg_pointer = (uint32_t *)((char *)esp + 4);
  *syscall_arg = malloc (4 * arg_num);
  int i;

  for (i = 0; i < arg_num; i++){

    if (!valid_memory (arg_pointer)){
      free(*syscall_arg);
      thread_current ()->exit_status = -1;
      thread_exit();
    }

    (*syscall_arg)[i] = *arg_pointer;
    arg_pointer += 1;
  }
}

static void sys_halt (void)
{
  shutdown_power_off(); 
}

static void sys_exit (uint32_t *syscall_arg){

  int status = syscall_arg[0];
  struct thread *t = thread_current ();

  t->exit_status = status;
  thread_exit ();
}

static void sys_exec (uint32_t *syscall_arg, uint32_t *eax){
 
  tid_t child_id;
  char *cmd_line = (char *)syscall_arg[0];
  struct thread *curr_thread = thread_current ();

  if (!valid_memory (cmd_line)){
    free (syscall_arg);
    curr_thread->exit_status = -1;
    thread_exit ();
  }

  child_id = process_execute (cmd_line);
  *(int *)eax = child_id;
  
}

static void sys_wait (uint32_t *syscall_arg, uint32_t *eax){

  tid_t pid = syscall_arg[0];
  *(int *)eax = process_wait (pid);
}

static void sys_create (uint32_t *syscall_arg, uint32_t *eax){

  void *file = (void *)syscall_arg[0];
  unsigned initial_size = syscall_arg[1];
  struct thread *cur = thread_current ();
  uint32_t success;

  if (!valid_memory (file)){
    free (syscall_arg);
    cur->exit_status = -1;
    thread_exit ();
  }

  if (strlen (file) > 100)
    success = 0;
  else {
   
    lock_acquire (&filesys_lock);
    success = (uint32_t)filesys_create (file, initial_size);
    lock_release (&filesys_lock);
  }

  *(uint32_t *)eax = success;
}

static void sys_remove (uint32_t *syscall_arg, uint32_t *eax){

  char *file_name = (char *)syscall_arg[0];
  uint32_t success;
  struct thread *cur = thread_current ();
  struct frame *ef_1, *ef_2;
  uint32_t name_len = strlen (file_name);
  bool check_twice = false;

  if (pg_ofs (file_name) != 0)
  {
    if ((uint32_t) (name_len + file_name) > (uint32_t) pg_round_up (file_name))
      check_twice = true;
  }

  if (!vm_with_pinning (file_name, &ef_1)){
    free (syscall_arg);
    cur->exit_status = -1;
    thread_exit ();
  }

  if (check_twice)
  {
    if (!vm_with_pinning (file_name + name_len, &ef_2)){
      free (syscall_arg);
      cur->exit_status = -1;
      thread_exit ();
    }
  }

  lock_acquire (&filesys_lock);
  success = filesys_remove (file_name);
  lock_release (&filesys_lock);

  ef_1->pinned = false;

  if (check_twice)
    ef_2->pinned = false;

  *(uint32_t *)eax = success;
}

static void sys_open (uint32_t *syscall_arg, uint32_t *eax){

  char *file_name = (char *)syscall_arg[0];
  struct file *opened_file;
  struct fd *fd_entry;
  struct thread *cur = thread_current ();
  struct frame *ef_1, *ef_2;
  uint32_t name_len = strlen (file_name);
  bool check_twice = false;

  if (pg_ofs (file_name) != 0)
  {
    if ((uint32_t) (name_len + file_name) > (uint32_t) pg_round_up (file_name))
      check_twice = true;
  }

  if (!vm_with_pinning (file_name, &ef_1)){
    free (syscall_arg);
    cur->exit_status = -1;
    thread_exit ();
  }
 
  if (check_twice)
  {
    if (!vm_with_pinning (file_name + name_len, &ef_2)){
     free (syscall_arg);
     cur->exit_status = -1;
     thread_exit ();
    }
  }

  lock_acquire (&filesys_lock);
  opened_file = filesys_open (file_name);
  lock_release (&filesys_lock);

  ef_1->pinned = false;

  if (check_twice)
    ef_2->pinned = false;

  if (opened_file != NULL){
 
    fd_entry = malloc (sizeof (struct fd));
    fd_entry->f = opened_file;
    fd_entry->fd_num = *eax = fd_index++;
    list_push_back (&cur->fd_list, &fd_entry->fd_elem);
  }
  else
    *(int *)eax = -1;

}
  
static void sys_filesize (uint32_t *syscall_arg, uint32_t *eax){
  
  int fd = syscall_arg[0];
  struct fd *fd_to_search = search_by_fd (fd);

  if (fd_to_search != NULL){

    lock_acquire (&filesys_lock);
    *eax = file_length (fd_to_search->f);
    lock_release (&filesys_lock);
  }
  else
    *eax = 0;

}

static void sys_read (uint32_t *syscall_arg, uint32_t *eax){
  
  int fd = syscall_arg[0];
  char *buffer = (char *)syscall_arg[1];
  unsigned size = syscall_arg[2];
  int i;
  struct fd *fd_to_read;

  if (fd == 0){
    for (i = 0; i < size; i++)
      buffer[i] = input_getc ();

    *eax = size;
  }
  else
  {
    fd_to_read = search_by_fd (fd);
    *eax = 0;

    if (fd_to_read != NULL){

      while (size > 0)
      {
        uint32_t byte_read;
        uint32_t br_candi;
        struct frame *earned_frame;

        if (pg_ofs (buffer) != 0)
          br_candi = (uint32_t)pg_round_up (buffer) - (uint32_t)buffer;   
        else
          br_candi = PGSIZE;

        byte_read = size < br_candi ? size : br_candi;

        if (!vm_with_pinning (buffer, &earned_frame))
        {
          free (syscall_arg);
          thread_current ()->exit_status = -1;
          thread_exit ();
        }

        lock_acquire (&filesys_lock);
        *eax += file_read (fd_to_read->f, buffer, byte_read);
        lock_release (&filesys_lock);
    
        size -= byte_read;
        buffer = (char *)buffer + byte_read;
        earned_frame->pinned = false;
      }
    }
  }
}

static void sys_write (uint32_t *syscall_arg, uint32_t *eax){
  
  int fd = syscall_arg[0];
  void *buffer = (void *)syscall_arg[1];
  unsigned size = syscall_arg[2];
  int printed_size = 0;
  struct fd *fd_to_write;

  if (fd == 1){

    while (size > 0){

      int print_size = size > 100 ? 100 : size;
      putbuf ((char *)buffer + printed_size, print_size);
      size -= print_size;
      printed_size += print_size; 
    }

    *(int *)eax = size;
  }
  else
  {
    fd_to_write = search_by_fd (fd);
    *eax = 0;

    if (fd_to_write != NULL){

      while (size > 0)
      {
        uint32_t byte_write;
        uint32_t bw_candi;
        struct frame *earned_frame;

        if (pg_ofs (buffer) != 0)
          bw_candi = (uint32_t)pg_round_up (buffer) - (uint32_t)buffer;
        else
          bw_candi = PGSIZE;

        byte_write = size < bw_candi ? size : bw_candi;

        if (!vm_with_pinning (buffer, &earned_frame))
        {
          free (syscall_arg);
          thread_current ()->exit_status = -1;
          thread_exit ();
        }

        lock_acquire (&filesys_lock);
        *eax += file_write (fd_to_write->f, buffer, byte_write);
        lock_release (&filesys_lock);

        size -= byte_write;
        buffer = (char *)buffer + byte_write;
        earned_frame->pinned = false;

      }
    }

  }
}

static void sys_seek (uint32_t *syscall_arg){

  int fd = syscall_arg[0];
  unsigned position = syscall_arg[1];
  struct fd *fd_to_seek = search_by_fd (fd);

  if (fd_to_seek != NULL){
    
    lock_acquire (&filesys_lock);
    file_seek (fd_to_seek->f, position);
    lock_release (&filesys_lock);
  }
}

static void sys_tell (uint32_t *syscall_arg UNUSED, uint32_t *eax UNUSED){

  printf("sys_tell!\n");
  thread_exit ();

}

static void sys_close (uint32_t *syscall_arg){

  int fd = syscall_arg[0];
  struct fd *fd_to_close = search_by_fd (fd);

  if (fd_to_close != NULL){
    
    lock_acquire (&filesys_lock);
    file_close (fd_to_close->f);
    lock_release (&filesys_lock);

    list_remove (&fd_to_close->fd_elem);
    free (fd_to_close);
  }
}

static void
syscall_handler (struct intr_frame *f) 
{  
  if (!valid_memory (f->esp)){
    thread_current ()->exit_status = -1;
    thread_exit();
  }

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
      sys_exec (syscall_arg, &f->eax);
      break;

    case SYS_WAIT :
      get_arg (&syscall_arg, 1, f->esp);
      sys_wait (syscall_arg, &f->eax);
      break;

    case SYS_CREATE :
      get_arg (&syscall_arg, 2, f->esp);
      sys_create (syscall_arg, &f->eax);
      break;
  
    case SYS_REMOVE :
      get_arg (&syscall_arg, 1, f->esp);
      sys_remove (syscall_arg, &f->eax);
      break;
    
    case SYS_OPEN :
      get_arg (&syscall_arg, 1, f->esp);
      sys_open (syscall_arg, &f->eax);
      break;

    case SYS_FILESIZE :
      get_arg (&syscall_arg, 1, f->esp);
      sys_filesize (syscall_arg, &f->eax);
      break;

    case SYS_READ :
      get_arg (&syscall_arg, 3, f->esp);
      sys_read (syscall_arg, &f->eax);
      break;

    case SYS_WRITE :
      get_arg (&syscall_arg, 3, f->esp);
      sys_write (syscall_arg, &f->eax);
      break;
    
    case SYS_SEEK :
      get_arg (&syscall_arg, 2, f->esp);
      sys_seek (syscall_arg);
      break;

    case SYS_TELL :
      get_arg (&syscall_arg, 1, f->esp);
      sys_tell (syscall_arg, &f->eax);
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


