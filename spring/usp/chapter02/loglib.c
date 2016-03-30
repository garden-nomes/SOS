#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "log.h"
 
typedef struct list_struct {
     data_t item;
     struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t data) {
    log_t *node;
    int nodesize;

    /* check data */
    if (data.string == NULL) {
        errno = EINVAL;
        return -1;
    }

    /* allocate node */
    nodesize = sizeof(log_t);
    if ((node = (log_t *)malloc(nodesize)) == NULL) {
        errno = ENOMEM;
        return -1;
    }

    node->item = data;

    /* append at the end of the list */
    if (headptr == NULL)
        headptr = node;
    if (tailptr != NULL)
        tailptr->next = node;
    tailptr = node;
    node->next = NULL;

    return 0;
}

void clearlog(void) {
    log_t *node;
    while (headptr != NULL) {
        node = headptr;
        headptr = headptr->next;

        /* clean up allocated memory */
        free(node);
    }
    tailptr = NULL;
    headptr = NULL;
}

char *getlog(void) {
    log_t *node;
    int logsize;
    char *log, *timestamp;

    /* calculate outputted log size */
    logsize = 1;
    for (node = headptr; node != NULL; node = node->next)
        logsize += strlen(ctime(&(node->item.time))) +
            strlen(node->item.string) + 3;

    /* allocate log */
    log = NULL;
    if ((log = malloc(logsize)) == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    /* write to log */
    log = strcpy(log, "");
    for (node = headptr; node != NULL; node = node->next) {
        timestamp = ctime(&(node->item.time));
        timestamp[strlen(timestamp) - 1] = '\0';    /* remove trailing newline */
        log = strcat(log, "[");
        log = strcat(log, timestamp);
        log = strcat(log, "] ");
        log = strcat(log, node->item.string);
        log = strcat(log, "\n");
    }

    return log;
}

int savelog(char *filename) {
    FILE *file;
    char *log;

    if ((file = fopen(filename, "a")) == NULL)
        return -1;

    log = getlog();
    fprintf(file, "%s", log);
    free(log);

    if (fclose(file))
        return -1;

    return 0;
}
