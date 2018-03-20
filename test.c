#include <stdlib.h>
#include <stdio.h>

int main() {
   while(1) {
       char c = getchar();
       int r = rand() % 100;
       printf("r: %d", r);
   }
   return 0;
}