#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define N 5

//flag for checking if the process the first child
int firstChild = 0;

//signal handler function
static void sigCatcher(int signo) {
    printf("PID %d caught one\n", getpid());
    //send signal only for the sibling of the child that is not the first one
    if(!firstChild) {
        kill(getpid() - 1, SIGUSR1);
    }
    exit(0);
}

int main(void) {

    int i, stat;
    pid_t pid[N];
    for (i=0; i<N; i++)
    {
        if (signal(SIGUSR1, sigCatcher) == SIG_ERR) {
            fputs("An error occurred while setting a signal handler.\n", stderr);
            return EXIT_FAILURE;
        }
        //create a child and perform its task
        if ((pid[i] = fork()) == 0)
        {
            printf("PID %d ready\n", getpid());
            sleep(1);
            //the first child will start the sequence of the signal raising
            if (i == 0) {
                firstChild = 1;
                kill(getpid() + N - 1, SIGUSR1);
            }
            sleep(1);
        }
    }

    //the father will wait for all of the zombies and finish afterwards
    for (i=0; i < N; i++)
    {
        pid_t cpid = waitpid(pid[i], &stat, 0);
        printf("Process %d is dead\n", pid[i]);
    }

    return EXIT_SUCCESS;
}
