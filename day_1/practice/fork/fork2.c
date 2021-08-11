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
    }
    else
    {
        printf("parent process\n");
    }
    
    return 0;
}