


#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h> 
#include <errno.h>
#include <string.h>


#include <stdio.h>
#include <fcntl.h>


int main(int argc, char * argv[])
{
    int p1 = 0;
    char tmp;
    int dp, f;
    char buf;
 
    p1 = fork();
 
    if(p1 != 0)
    {
        printf("\nSERVEUR WAIT  %d  ..\n", p1 );
        wait(NULL);
    }
    else
    {
        printf("\nEXECUTION CLIENT\n" );
        execl("/usr/bin/xterm" , "xterm", "-e", "./Client", "Client", NULL);
    }
 
    return 0;
}






/* Filename: fifoserver.c */
/*
#define FIFO_FILE "MYFIFO"
int main() {
   int fd;
   char readbuf[80];
   char end[10];
   int to_end;
   int read_bytes;
   
   // Create the FIFO if it does not exist 
   mknod(FIFO_FILE, S_IFIFO|0777, 0);
   strcpy(end, "end");
   while(1) {
      fd = open(FIFO_FILE, O_RDONLY);
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      printf("Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      to_end = strcmp(readbuf, end);
      if (to_end == 0) {
         close(fd);
         break;
      }
   }
   return 0;
}
*/


/*
int main(int argc, char * argv[]){
    int p1 = 0;
    int tmp = 25310;
    int dp, f;
    char buf;

    unlink("pipe");
    mkfifo("pipe" ,0666);


    p1 = fork();
    if(p1 != 0)
    {
    	printf("\np1 != 0\n" );
        dp=open("pipe",O_WRONLY);
        write(dp, &tmp,sizeof(int));
        close(dp);
    }
    else
    {
    	printf("\nEXECUTION CLIENT\n" );
        execv("Client",NULL);
    }
    printf("\n\n\n\n\n\nHELLOO\n\n\n\n");

    return 0;
}
*/