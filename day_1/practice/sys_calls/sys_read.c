#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFF_SIZE 50
int main()
{
   int fd;
   unsigned char buff[BUFF_SIZE];

   fd = open("write.txt", O_RDONLY , S_IRUSR | S_IWUSR);

   if(-1 == fd)
   {
       perror("error opening file");
       exit(EXIT_FAILURE);
   }

   read(fd, buff, BUFF_SIZE);
   printf("read data from file: %s\n", buff);

   close (fd);

   exit(EXIT_SUCCESS);

}