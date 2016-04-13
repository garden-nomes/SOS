#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int i, sleep_time, repeat;

    /* check usage */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s sleep-time repeat", argv[0]);
        return 1;
    }

    sleep_time = atoi(argv[1]);
    repeat = atoi(argv[2]);

    for (i = 0; i < repeat; ++i) {
        sleep(sleep_time);
        fprintf(stderr, "[%ld] running %d more time(s)\n",
            (long)getpid(), repeat - i - 1);
    }
}