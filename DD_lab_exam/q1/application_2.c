#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
        int fd;
        char Ubuff[80] = "hello  kernel this is the user1";
        char Kbuff[80];

                fd = open("/dev/mydev",O_RDWR);
        if (fd<0)
        {
                printf("error openning file");
                exit(1);
        }
        write(fd,Ubuff,80);
        read(fd,Kbuff,sizeof(Kbuff));
        printf("read value = %s\n",Kbuff);
        close(fd);
        return 0;
}
