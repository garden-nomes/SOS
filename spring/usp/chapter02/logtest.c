#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

#ifndef MAX_CANON
#define MAX_CANON 8192
#endif

#define PROMPT  "> "
#define GREETING    "L0gg3r Pro v0.1\n"                               \
                    "Noah Weiner, USP16\n"                            \
                    "-----------------------\n"
#define HELP        "\nCommands:\n"                                   \
                    "   help : print command list\n"                  \
                    "   log : print log to stdout\n"                  \
                    "   save [filename] : print log to [filename]\n"  \
                    "   clear : clear the log\n"                      \
                    "   quit : what it sounds like\n"                 \
                    "   anything else gets written to the log\n"


int logmsg(const char *msg) {
    data_t item;

    if (time(&(item.time)) == -1)   /* set item.time to current time */
        return -1;
    /* if we don't copy msg, every log entry will point to the same string */
    item.string = malloc(strlen(msg) + 1);
    strcpy(item.string, msg);
    return addmsg(item);    /* append log */
}

int main(int argc, char **argv) {
    char input[MAX_CANON], msg[MAX_CANON];
    char *log;

    printf(GREETING);
    printf(HELP);

    while (1) {
        /* grab input */
        printf(PROMPT);
        if (fgets(input, MAX_CANON, stdin) == NULL)
            break;

        /* remove trailing newline */
        if (*(input + strlen(input) - 1) == '\n')
            *(input + strlen(input) - 1) = 0;

        /* process input */
        if (!strcmp(input, "quit"))
            break;
        else if (!strcmp(input, "log")) {
            printf("%s", (log = getlog()));
            free(log);
        } else if (!strncmp(input, "save", 4)) {
            savelog(input + 5); /* first trim first 5 chars */
        } else if (!strcmp(input, "clear"))
            clearlog();
        else if (!strcmp(input, "help"))
            printf(HELP);
        else if (logmsg(input))
            perror("Unable to log message");
    }

    return 0;
}
