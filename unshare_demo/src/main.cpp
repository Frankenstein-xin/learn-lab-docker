/**
 * Source: https://man7.org/linux/man-pages/man2/clone.2.html
 */
#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE);} while (0)

static void usage(char *pname) {
    fprintf(stderr, "Usage: %s [options] program [arg...]\n", pname);
    fprintf(stderr, "Options can be:\n");
    fprintf(stderr, "    -i   unshare IPC namespace\n");
    fprintf(stderr, "    -m   unshare mount namespace\n");
    fprintf(stderr, "    -n   unshare network namespace\n");
    fprintf(stderr, "    -p   unshare PID namespace\n");
    fprintf(stderr, "    -u   unshare UTS namespace\n");
    fprintf(stderr, "    -U   unshare user namespace\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int flags, opt;

    flags = 0;

    while ((opt = getopt(argc, argv, "imnpuU")) != -1) {
        switch (opt) {
        case 'i':
            flags |= CLONE_NEWIPC;
            break;
        case 'm':
            flags |= CLONE_NEWNS;
            break;
        case 'n':
            flags |= CLONE_NEWNET;
            break;
        case 'p':
            flags |= CLONE_NEWPID;
            break;
        case 'u':
            flags |= CLONE_NEWUTS;
            break;
        case 'U':
            flags |= CLONE_NEWUSER;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (optind >= argc) {
        usage(argv[0]);
    }
    

    if (-1 == unshare(flags)) {
        errExit("unshare");
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