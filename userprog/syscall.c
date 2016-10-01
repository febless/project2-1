#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/ArrayList.h"

static void syscall_handler (struct intr_frame *);

void syscall_init (void){
	/*init struct Files */
	initWithSize(Files, 100);
	intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void halt(void){
	shutdown_power_off();
}

void exit(int status){
	
  struct thread *current = thread_current();
  struct child_process* cp = get_child_process(pid); 
  if(thread_alive(current->parent)){
	  cur->cp->status =status;
  }
  printf("%s:exit(%d)\n", cur->name, status);
  thread_exit();	
}

pid_t exec(const char* cmd_line){
	
  pid_t pid = process_execute(cmd_line);
  struct child_process* cp = get_child_process(pid);
  ASSERT(cp);
  while(cp->load==NOT_LOADED){
	  barrier();
  }
 if (cp->load == LOAD_FAIL){
	 return ERROR;
  }
   return pid;
}

int wait(pid_t pid){
	
  return process_wait(pid); 
}

bool create(const char* file, unsigned initial_size){
	return filesys_create(file, initial_size);
}

bool remove(const char* file){
	return filesys_remove(file);
}

int open(const char* file){
	struct file* fd = filesys_open(file);
	if(fd == NULL){
		return -1;
	}
	return add(&Files, file);
}

struct file* findFile(int fd){
	int i;
	for(i = 0; i < Files.size; i ++){
		if(Files.get(i).fd == fd){
			return filesys_open(get(&Files, i) -> file_name);
		}
	}
	return NULL;
}

const char* findFileChar(int fd){
	int i;
	for(i = 0; i < Files.size; i ++){
		if(Files.get(i).fd == fd){
			return get(&Files, i) -> file_name;
		}
	}
	return NULL;
}

int filesize(int fd){
	return file_length(findFile(fd));
}

int read(int fd, void* buffer, unsigned size){
	if(fd == 0){
		input_getc();
	}else{
		return file_read(findFile(fd), buffer, size);
	}
}

int write(int fd, const void* buffer, unsigned size){
	if(fd == 1){
		unsigned size_copy = size;
		unsigned max = 128;
		while(size_copy > max){
			/* break into chunks */
			putbuf(buffer, max);
			buffer += max;
			size_copy -= max;
		}
		putbuf(buffer, size_copy);
		return size;
	}else{
		return file_write(findFile(fd), buffer, size);
	}
}

void seek(int fd, unsigned position){
	file_seek(findFile(fd), position);
}

unsigned tell(int fd){
	return findFile(fd)->pos;
}

void close(int fd){
	file_close(findFile(fd));
	int index = indexOf(Files, findFileChar(fd));
	removeAt(Files, index);
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  thread_exit ();
}
