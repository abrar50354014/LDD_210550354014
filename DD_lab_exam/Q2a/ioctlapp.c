#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/ioctl.h>
#include"ioctll.h"

int main()
{

	int fd,baudrate = 9600;
	int res;

	fd = open("/dev/ioctldev",O_RDWR);

	if(fd<0)
	{
		printf("error");
		return 0;
	}
	
	ioctl(fd,SET_BAUDRATE,(int *)&baudrate);
	ioctl(fd,SEND_BAUDRATE,(int *) &res);
        printf("Read Value %d",res);
	close(fd);
	return 0;	
}


