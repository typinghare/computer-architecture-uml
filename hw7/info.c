#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    char msg_buf[100];
    int msg_pipe[2];

    // use the pipe() system call to create the pipe
    if (pipe(msg_pipe) == -1) {
        perror("failed in Parent pipe creation:");
        exit(7);
    }

    // use various system calls to collect and print process details
    printf("\nThis is the Parent process report:\n");
    const pid_t pid = getpid();
    const pid_t ppid = getppid();
    const int ruid = getuid();
    const int euid = geteuid();
    const int rgid = getgid();
    const int egid = getegid();
    const int priority = getpriority(PRIO_PROCESS, 0);

    printf(
        "\nPARENT PROG:  Process ID is:\t\t%d\n\
PARENT PROC:  Process parent ID is:\t%d\n\
PARENT PROC:  Real UID is:\t\t%d\n\
PARENT PROC:  Real GID is:\t\t%d\n\
PARENT PROC:  Effective UID is:\t\t%d\n\
PARENT PROC:  Effective GID is:\t\t%d\n\
PARENT PROC:  Process priority is:\t%d\n",
        pid, ppid, ruid, rgid, euid, egid, priority);

    printf("\nPARENT PROC: will now create child, write pipe,\n \
and do a normal termination\n");

    // use the sprintf() call to build a message to write into the pipe
    // and dont forget to write the message into the pipe before parent exits
    //


    // now use the fork() call to create the child:
    //
    // format is:
    //
    // 	switch (pid = fork()){
    //        case -1: // if the call fails
    //
    //        default: // this is the parent's case
    //                 // parent must write message to pipe and
    //                 // do a normal exit
    //
    //        case 0:  // this is the child's case
    //		   // child must create and print report
    //                 // child must read pipe message and print
    //		   // a modified version of it to output
    //		   // child must do a normal exit

    read(msg_pipe[0], msg_buf, 100);

    printf("CHILD PROC: parent's msg is %s\n", msg_buf);
    printf("CHILD PROC: Process parent ID now is:   %d\n", getppid());
    printf("CHILD PROC: ### Goodbye ###\n");
    exit(0);
}  // switch and child end
