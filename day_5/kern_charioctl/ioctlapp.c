#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<linux/ioctl.h>
#include<unistd.h>
#include<sys/stat.h>
#include "ioctl.h"
#include "cal.h"
int main()
{
   int num;
   int fd;
   int32_t res,num1,num2;

    fd = open("/dev/charioctl",O_RDWR);

    if(fd<0) 
	{
        	printf("error opening file ...\n");
        	return 0;
    	}

    	printf("Operation to perform\n");
    	printf("\n1. ADD\t 2. SUB\t 3. MUL\t 4. DIV\n");

     scanf("%d",&num);
   
    if(num > 4 && num < 1)
        {
        	printf("Enter between 1 and 4");
        	return 0;
        }
    ioctl(fd,WR_VALUE,(int*) &num);

    printf("Enter first value :");
    scanf("%d",&num1);

    printf("Enter second value :");
    scanf("%d",&num2);

    printf("writing value to driver\n");
    ioctl(fd,WR_VALUE,(int*) &num1);
    ioctl(fd,WR_VALUE,(int*) &num2);

    printf("reading value from driver\n");
    ioctl(fd,RD_VALUE,(int*)&res);
    printf("value is %d\n",res);
    close(fd);
}
