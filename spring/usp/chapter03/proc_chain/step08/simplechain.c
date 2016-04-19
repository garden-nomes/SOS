#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1000

int main (int argc, char *argv[]) {
   pid_t childpid = 0;
   int i, j, n, nchars;
   char mybuf[BUF_SIZE];

   if (argc != 3){   /* check for valid number of command-line arguments */
      fprintf(stderr, "Usage: %s processes nchars\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);
   nchars = atoi(argv[2]);
   if (nchars > BUF_SIZE) {
       fprintf(stderr, "Invalid input: nchars cannot be larger than %d\n", BUF_SIZE);
       return 1;
   }
   for (i = 1; i < n; i++)
      if (childpid = fork())
         break;

   for (j = 0; j < nchars; j++)
       mybuf[j] = getchar();
   mybuf[j] = 0;
   fprintf(stderr, "%ld:%s", (long)getpid(), mybuf);
   return 0;
}
