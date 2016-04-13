#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include "restart.h"

#ifndef MAX_CANON
#define MAX_CANON 8192
#endif

int main(int argc, char* argv[]) {
    int pr_limit, pr_count;
    char buf[MAX_CANON];
    pid_t pid;

    /* check usage */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1;
    }

    pr_limit = atoi(argv[1]);   /* max concurrent processes */
    if (pr_limit < 1) pr_limit = 1;
    pr_count = 0;   /* current concurrent processes */

    while (fgets(buf, MAX_CANON, stdin) != NULL) {  /* read until EOF */
        /* if we've hit pr_limit, wait until a child finishes */
        if (pr_count == pr_limit) {
            if ((pid = r_wait(NULL)) == -1) {
                if (errno == ECHILD) pr_count = 0;
                perror("waitpid");
            } else {
                --pr_count;
                fprintf(stderr, "-=- [%ld] exited -=-\n", (long)pid);
            }
        }

        /* fork and execute command */
        if ((pid = fork()) == 0) {
            system((char *)buf);
            exit(0);
        } else if (pid == -1)
            perror("fork");
        else {
            fprintf(stderr, "-=- [%ld] started -=-\n", (long)pid);
            ++pr_count;
        }

        /* check for any completed children */
        while ((pid = waitpid(-1, NULL, WNOHANG)) != 0) {
            if (pid == -1) {
                if (errno == ECHILD) pr_count = 0;
                perror("waitpid");
            } else {
                --pr_count;
                fprintf(stderr, "-=- [%ld] exited -=-\n", (long)pid);
            }
        }
    }

    /* wait for all children to finish */
    while (pr_count > 0) {
        if ((pid = r_wait(NULL)) == -1) {
            if (errno == ECHILD) pr_count = 0;
            perror("waitpid");
        } else {
            --pr_count;
            fprintf(stderr, "-=- [%ld] exited -=-\n", (long)pid);
        }
    }

    return 0;
}