#include <stdlib.h>
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
    int nodesize = sizeof(node) + strlen(data.string) + 1;

    /* allocate node */
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

    return 0;
}

void clearlog(void) {
    log_t *node;
    tailptr = NULL; /* reset tail pointer */
    while (headptr != NULL) {
        node = headptr;
        headptr = headptr->next;

        /* clean up allocated memory */
        free(node->item.string);
        free(node);
    }
}

char *getlog(void) {
    log_t *node;
    int logsize;
    char *log, *timestamp;

    if (headptr == NULL)    /* empty log! */
        return "";

    /* calculate outputted log size */
    logsize = 1;
    for (node = headptr; node != NULL; node = node->next)
        logsize += strlen(ctime(&(node->item.time))) + strlen(node->item.string) - 10;

    /* allocate log */
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
   return 0;
}
