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
