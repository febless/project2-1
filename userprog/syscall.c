#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void syscall_init (void){
	intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void halt(void){

}

void exit(int status){

}

pid_t exec(const char* cmd_line){

}

int wait(pid_t pid){

}

bool create(const char* file, unsigned initial_size){
	/* create file */
	fd = creat(file, S_IREAD | S_IWRITE);
	if(fd == -1)
		return FALSE;
		/* perror("error creating a data file"); */
	/* initialize size */
	FILE *fp = fopen(file, "w");
	fseek(fp, initial_size, SEEK_SET);
	fputc('\0', fp);
	fclose(fp);
	/* Note that in c, in order to initialize a file size,
	 * must open the file first, */
	return TRUE;
}

bool remove(const char* file){
	/* unable to use remove() since it will be recursion */
	status = unlink(file);
	if(status == -1)
		return FALSE;
	return TRUE;
}

int open(const char* file){

}

int filesize(int fd){

}

int read(int fd, void* buffer, unsigned size){

}

int write(int fd, const void* buffer, unsigned size){

}

void seek(int fd, unsigned position){

}

unsigned tell(int fd){

}

void close(int fd){

}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  thread_exit ();
}
