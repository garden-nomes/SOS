#include <errno.h>
#include <stdlib.h>
#include <string.h>

int makeargv(const char *s, const char *delimiters, char ***argvp) {
   int error;
   int i;
   int numtokens;
   const char *snew;
   char* saveptr;   /* used internally by strtok_r */
   char *t;

   if ((s == NULL) || (delimiters == NULL) || (argvp == NULL)) {
      errno = EINVAL;
      return -1;
   }
   *argvp = NULL;                           
   snew = s + strspn(s, delimiters);         /* snew is real start of string */
   if ((t = malloc(strlen(snew) + 1)) == NULL) 
      return -1; 
   strcpy(t, snew);               
   numtokens = 0;
   if (strtok_r(t, delimiters, &saveptr) != NULL)     /* count the number of tokens in s */
      for (numtokens = 1; strtok_r(NULL, delimiters, &saveptr) != NULL; numtokens++) ; 

                             /* create argument array for ptrs to the tokens */
   if ((*argvp = malloc((numtokens + 1)*sizeof(char *))) == NULL) {
      error = errno;
      free(t);
      errno = error;
      return -1; 
   } 
                        /* insert pointers to tokens into the argument array */
   if (numtokens == 0) 
      free(t);
   else {
      strcpy(t, snew);
      **argvp = strtok_r(t, delimiters, &saveptr);
      for (i = 1; i < numtokens; i++)
          *((*argvp) + i) = strtok_r(NULL, delimiters, &saveptr);
    } 
    *((*argvp) + numtokens) = NULL;             /* put in final NULL pointer */
    return numtokens;
}     