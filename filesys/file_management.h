#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/ArrayList.h"

static struct ArrayList Files;

struct each_file{
	struct file* file_hold;
	int fd;
};

#endif /* userprog/process.h */
