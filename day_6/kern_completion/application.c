#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
int main()
{
	int fd;
	char Wbuff[] = "hello kernal.... this is user";
	char Rbuff[] = "\0";

	fd = open("/dev/compdevice",O_RDWR);
	
	if(fd<0)
	{
		printf("\nerror opening file\n");
		exit(1);
	}
	if(fork() == 0)//child
	{
		write(fd,Wbuff,sizeof(Wbuff));

	}
	//parent
	else
	{
		read(fd,Rbuff,sizeof(Rbuff));

		printf("Value read: %s\n",Rbuff);
		wait(NULL);
	}

	close(fd);
	return 0;
}
