#include <unistd.h>
#include <fcntl.h>

#define WRITE_CHAR "x"

int waitatbarrier(char *name) {
    char *name_release, *name_request;
    int fd;
    char buf[1];

    if (asprintf(&name_release, "%s.release", name) == -1 ||
        asprintf(&name_request, "%s.request", name) == -1)
        return -1;

    if ((fd = open(name_request, O_WRONLY)) == -1 ||
        write(fd, (void *)WRITE_CHAR, 1) == -1 ||
        close(fd) == -1) {
        perror("Failed to write to request pipe");
        return -1;
    }

    if ((fd = open(name_release, O_RDONLY)) == -1 ||
        read(fd, buf, 1) == -1 ||
        close(fd) == -1) {
        perror("Failed to read from release pipe");
        return -1;
    }

    return 0;
}
