#ifndef FILESYS_ARRAYLIST_H
#define FILESYS_ARRAYLIST_H

#include "filesys/filesys.h"
#include "filesys/file.h"

typedef struct{
	const char* file_name;
	int fd;
} Element;

typedef struct{
	int current;
	int size;
	int increment_rate;
	Element* elements;
} ArrayList;

static ArrayList Files;

typedef enum{
    RIFHT, LEFT
} Shift;

// public functions:
void        init           (ArrayList*const);
void        initWithSize   (ArrayList*const, int);
void        initWithSizeAndIncRate    (ArrayList*const, int, int);
Element*    get            (ArrayList*const, int);
int         add            (ArrayList*const, const char* file);
Element*    removeAt       (ArrayList*const, int);
int         indexOf        (ArrayList*const, const char* file);

/*
void        clean          (ArrayList*);
int         insert         (ArrayList*const, Element, int);
void        clear          (ArrayList*const);
int         set            (ArrayList*const, Element, int);
void        print          (const ArrayList*const);
int         lastIndexOf    (const ArrayList*const, Element);
int         isEmpty        (const ArrayList*const);
// TODO
int        hashCode        (const ArrayList*const);
*/

// static (private) utility functions:

/* Abstracting the print method of the element by delegating it to the element itself (OOP-like feature) */
//static void    printElement(const Element*const);
void    shift(ArrayList *const list, int index, int rooms, Shift dir);
void    wide(ArrayList* const);

#endif /* filesys/ArrayList.h */
