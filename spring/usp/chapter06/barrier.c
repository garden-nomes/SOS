#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char *name_release, *name_request;

void unlink_pipes(void) {
    if (unlink(name_release) == -1 ||
        unlink(name_request) == -1) {
        perror("Couldn't destroy pipes");
        _exit(1);
    }
}

int main(int argc, char *argv[]) {
    int n, i;
    int fd;

    if (argc != 3 || (n = atoi(argv[2])) <= 0) {
        fprintf(stderr, "Usage: %s pipe processes\n", argv[0]);
        return -1;
    }

    /* generate pipe names */

    if (asprintf(&name_release, "%s.release", argv[1]) == -1 ||
        asprintf(&name_request, "%s.request", argv[1]) == -1) {
        perror("Couldn't create pipe names");
        return 1;
    }

    char buf[n];

    /* make pipes */

    if ((mkfifo(name_release, FIFO_PERMS) == -1 ||
        mkfifo(name_request, FIFO_PERMS) == -1) && errno != EEXIST) {
        perror("Couldn't create named pipes");
        return 1;
    }

    if (atexit(unlink_pipes) == -1)
        perror("Couldn't register atexit");

    /* main loop */

    while (1) {
        if ((fd = open(name_request, O_RDONLY)) == -1) {
            perror("Couldn't open request pipe for reading");
            return -1;
        }

        for (i = 0; i < n; i += read(fd, (void *)buf, n));

        if (close(fd) == -1)
            perror("Couldn't close request pipe");

        fprintf(stderr, "[server] breaking barrier...\n");

        if ((fd = open(name_release, O_WRONLY)) == -1) {
            perror("Couldn't open release pipe for writing");
            return -1;
        } else if (write(fd, (void *)buf, n) == -1) {
            perror("Couldn't read from release pipe");
            return -1;
        } else if (close(fd) == -1)
            perror("Couldn't close release pipe");
    }


    return 0;
}