#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd;
	char Ubuff[100] = "hello  kernel this is user";
        char Kbuff[100];

		fd = open("/dev/ioctldev",O_RDWR,07770);
	if (fd<0)
	{
		printf("error openning file");
		exit(1);
	}
	write(fd,Ubuff,sizeof(Ubuff));
	read(fd,Kbuff,sizeof(Kbuff));
	printf("read value = %s\n",Kbuff);
	close(fd);
	return 0;	
}
