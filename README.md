c-garbage-collector
===================

A garbage collector for C hacked using mcheck standard library

Usage
=====
1: run 'export MALLOC_TRACE=/tmp/mtrace_logs'
2: Include mtrace_gc.h in the preprocessor directives of your C code
3: Before you allocate any memory, make a call to mtrace()
4: Before you exit the function/program, call muntrace() and gc() consecutively
5: Compile the program in gcc with flags -g and -w

Example
=======
#include"mtrace_gc.h"

int main() {
   char *ptr1;
   char *ptr2;
   mtrace();
   ptr1 = (char *)malloc(sizeof(char));
   ptr2 = (char *)malloc(sizeof(char));
   free(ptr2);
   muntrace();
   gc();
}

Behind the scenes
=================
What this library actually does is that it uses mtrace's functionalities.
mtrace is a part of mcheck standard library in C. When a call to mtrace() is made, it begins logging the memory allocations and deallocations in a file specified in the MALLOC_TRACE bash variable. It stops logging when a call to muntrace() is made. So what is done here is that when gc() is called, it reads the file into which mtrace has written, and reads the address of the unfreed memory block, and frees it!!