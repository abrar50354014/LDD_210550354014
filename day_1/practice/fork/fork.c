#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t id;
    
    printf("parent: %d\n", getpid());
    id = fork();
    printf("after fork: %d\n", getpid());
    printf("id: %d\n", id);
    return 0;
}