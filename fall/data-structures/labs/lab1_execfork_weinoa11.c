/*
 * Lab 1: exec and fork
 * Noah Weiner
 *
 * Resubmitted because I made this slightly less stupid
 * in that it loops, like a real shell.
 */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PROMPT "%s> ", argv[0]

/*
 * This is Program 2.2 from the USP book ... it is an exercise
 * in constructing the argv array from a command line string.
 * Slight alterations by SJS
 */

int makeargv(const char *s, const char *delimiters, char ***argvp) {
	int error;
	int i;
	int numtokens;
	/*
	 * Note that const char * says the data is const, not the pointer.
	 */
	const char *snew;
	char *t;

	if ((s == NULL) || (delimiters == NULL) || argvp == NULL) {
		errno = EINVAL;
		return -1;
	}

	*argvp = NULL;
	/* skip any leading delimiters */
	snew = s + strspn(s, delimiters);
	if ((t = malloc(strlen(snew) + 1)) == NULL)
		return -1;
	strcpy(t, snew);
	numtokens = 0;
	if (strtok(t, delimiters) != NULL)
	for(numtokens = 1;  strtok(NULL, delimiters) != NULL; numtokens++)
			;
	if ((*argvp = malloc((numtokens+1)*sizeof(char *))) == NULL) {
		error = errno;
		free(t);
		errno = error;
		return -1;
	}

	if (numtokens == 0)
		free(t);
	else {
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for(i=1; i<numtokens; i++)
			*((*argvp)+i) = strtok(NULL, delimiters);
	}
	*((*argvp)+numtokens) = NULL;
	return numtokens;
}

int main(int argc, char* argv[]) {
	char input[128];
	char* newEnviron[] = {NULL};
	while (1) {

		/* get input */
		printf(PROMPT);
		gets(input);	/* I know gets is bad, but scanf was reading
						   reading from stdout for some reason. */

		/* create args */
		char** newArgv;
		int newArgc;
		newArgc = makeargv(input, " ", &newArgv);

		/* check for exit */
		if (strcmp(newArgv[0], "exit") == 0)
			exit(EXIT_SUCCESS);

		/* fork */
		pid_t pid = fork();
		if (pid == 0) {	/* child process */

			/* execute command */	
			execve(newArgv[0], newArgv, newEnviron);

			/* no return on error */
			perror("execve");
			exit(EXIT_FAILURE);

		} else {		/* parent process */

			/* wait for child process and exit */
			waitpid(pid, NULL, 0);

		}

	}
}
