/**
 * Source: https://man7.org/linux/man-pages/man2/clone.2.html
 */
#define _GNU_SOURCE
#include <sched.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define STACK_SIZE (1024 * 1024) 
#define errExit(msg)  do { perror(msg); exit(EXIT_FAILURE);} while (0)

static char child_stack[STACK_SIZE];

static int child_func(void *arg) {
    struct utsname uts;
    
    /* modify hostname, acturely in another namespace */
    if (-1 == sethostname((const char *)arg, strlen((const char *)arg))) {
        errExit("sethostname");
    }

    if (-1 == uname(&uts)) {
        errExit("uname");
    }

    cout << "uts.nodename in child: " << uts.nodename << endl;


    /* Keep the namespace open for a while, by sleeping.
       This allows some experimentation--for example, another
       process might join the namespace. */
    sleep(100);

    return 0;   /* Terminates child */
}


int main(int argc, char *argv[]) {

    pid_t child_pid;
    struct utsname uts;
    /**
     * The child termination signal
       When the child process terminates, a signal may be sent to the
       parent.  The termination signal is specified in the low byte of
       flags (clone()) or in cl_args.exit_signal (clone3()).  If this
       signal is specified as anything other than SIGCHLD, then the
       parent process must specify the __WALL or __WCLONE options when
       waiting for the child with wait(2).  If no signal (i.e., zero) is
       specified, then the parent process is not signaled when the child
       terminates.
     */

    // SIGCHLD, signal sent to parent when child dies
    child_pid = clone(child_func, child_stack + STACK_SIZE, CLONE_NEWUTS | SIGCHLD, (void *)"lalala");

    if (-1 == child_pid)
        errExit("clone");

    printf("PID of child created by clone() is %d\n", child_pid);

    sleep(1);

    if (uname(&uts) == -1)
        errExit("uname");

    printf("uts.nodename in parent: %s\n", uts.nodename);


    if (waitpid(child_pid, NULL, 0) == -1)
        errExit("waitpid");
    printf("child has terminated\n");

    exit(EXIT_SUCCESS);
}