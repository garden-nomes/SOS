#include <stdio.h>
#include "log.h"

int logmsg(char *msg) {
    data_t item;

    if (time(&(item.time)) == -1)   /* get current time */
        return -1;
    item.string = msg;  /* set message */
    return addmsg(item);    /* append log */
}

int main(int argc, char **argv) {
    char *logstring;

    printf("Writing to the log...\n");

    if (logmsg("This is a test!") == -1)
        perror("Unable to append log");
    if (logmsg("Does the loger work?") == -1)
        perror("Unable to append log");
    if (logmsg("If you're reading this, I guess so!") == -1)
        perror("Unable to append log");

    if ((logstring = getlog()) == NULL)
        perror("Unable to read log");

    printf("\nLog:\n%s", logstring);

    return 0;
}
