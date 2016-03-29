#include <stdio.h>
#include <string.h>

extern char **environ;

int main(void) {
   int i;
   char *key, *value;
   const char *delims = "=";

   printf("The environment list follows:\n");

   for(i = 0; environ[i] != NULL; i++) {
       if ((key = strtok(environ[i], delims)) == NULL ||
           (value = strtok(NULL, delims)) == NULL)
           fprintf(stderr, "Unable to tokenize environ %s.\n", environ[i]);
       else
           printf("%s: %s\n", key, value);
   }

   return 0;
}
