#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

 int main(int argc , char* argv []) {
   int seconds = atoi(argv[1]);
   printf("Sleeping for %d seconds\n", seconds);
   sleep (seconds) ;
   return 0;
 }