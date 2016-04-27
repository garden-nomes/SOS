#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int waitatbarrier(char *name);

int main (int argc, char *argv[]) {
   pid_t childpid = 0;
   int i, h, n;

   srand(time(NULL));

   if (argc != 4 || (n = atoi(argv[2])) <= 0 || (h = atoi(argv[3])) <= 0) {
      fprintf(stderr, "Usage: %s pipe processes loops\n", argv[0]);
      return 1;
   }

   fprintf(stderr, "[%ld] forking children...\n", (long)getpid());
   for (i = 1; i < n; i++)
      if ((childpid = fork()) <= 0)
         break;

   int seed = (int)getpid();

   int j;
   for (j = 0; j < 4; j++) {
       fprintf(stderr, "[%ld] starting loop j=%d...\n", (long)getpid(), j);
       sleep(rand_r(&seed) % 10);
       fprintf(stderr, "[%ld] waiting at barrier...\n", (long)getpid());
       if (waitatbarrier(argv[1]) == -1) {
           perror("Error while waiting for barrier");
           return -1;
       }
   }

   return 0; 
}
