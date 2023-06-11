/**
 * Source: https://man7.org/linux/man-pages/man2/clone.2.html
 */
#define _GNU_SOURCE
#include <sched.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE);} while (0)

int main(int argc, char *argv[]) {
    int fd;

    if (argc < 3) {
        fprintf(stderr, "%s /proc/PID/ns/FILE cmd [arg...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    cout << "My PID: " << getpid() << endl;

    /**
     * fd represents the file descriptor this thread will join, which is opened use the file path of argv[1]
     */
    fd = open(argv[1], O_RDONLY);

    if (-1 == fd) {
        errExit("open");
    }

    if (-1 == setns(fd, 0)) {
        errExit("setns");
    }

    /**
     * What is execvp?
     * https://www.digitalocean.com/community/tutorials/execvp-function-c-plus-plus
     * Run a cmd or executive file that in current PATH, note that if your cmd or exccutive file not in PATH, it will not functional
     * When running `execvp`, our program is totally give the control to command, that means, run in the same PID,
     * So, anything that comes after execvp() will NOT execute, since our program is taken over completely!
     */
    execvp(argv[2], &argv[2]);

    // Will never reaches here
    errExit("execvp");
}
