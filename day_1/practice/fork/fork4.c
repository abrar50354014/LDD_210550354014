#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t id;
    
    printf("parent: %d\n", getpid());
    id = fork();

    if(0 == id)
    {
        printf("child process\n");
        sleep(6);
        printf("child PID: %d\n", getpid());
        printf("child PPID: %d\n", getppid());
        printf("child ID: %d\n", id);
    }
    else
    {
        printf("parent process\n");
        //sleep(6);
        printf("parent PID: %d\n", getpid());
        printf("parent PPID: %d\n", getppid());
        printf("parent ID: %d\n", id);
    }
    
    return 0;
}
