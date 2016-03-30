#include <stdio.h>
#include <stdlib.h>
#include "log.h"

int logmsg(char *msg) {
    data_t item;

    if (time(&(item.time)) == -1)   /* get current time */
        return -1;
    item.string = msg;  /* set message */
    return addmsg(item);    /* append log */
}

int main(int argc, char **argv) {
    char *log;

    printf("Writing to the log... ");
    if (logmsg("This is a test!") == -1)
        perror("Unable to append log");
    if (logmsg("Does the loger work?") == -1)
        perror("Unable to append log");
    if (logmsg("If you're reading this, I guess so!") == -1)
        perror("Unable to append log");
    printf("done!\n");

    log = getlog();
    printf("\nLog:\n%s\n", log);
    free(log);

    printf("Clearing log... ");
    clearlog();
    printf("done!\n");

    log = getlog();
    printf("\nLog:\n%s\n", log);
    free(log);

    printf("Writing to the log (again)... ");
    if (logmsg("Wow it works pretty well!") == -1)
        perror("Unable to append log");
    if (logmsg("Yeah?") == -1)
        perror("Unable to append log");
    if (logmsg("Pretty cool right?") == -1)
        perror("Unable to append log");
    printf("done!\n");

    log = getlog();
    printf("\nLog:\n%s\n", log);
    free(log);

    return 0;
}
