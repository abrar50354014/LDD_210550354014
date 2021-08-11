#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
   int fd;

   fd = open("write.txt", O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);

   if(-1 == fd)
   {
       perror("error opening file");
       exit(EXIT_FAILURE);
   }

   write(fd, "hello\n", 5);

   close (fd);

   exit(EXIT_SUCCESS);

}