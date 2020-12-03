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

#define BUFFERSIZE 100

//volatile int stopLecture;

int flag = 1;


void catchCtrlC()
{
   flag = 0;
   printf("passe ctrl C\n");
}


void stop(int sig){
    printf("CLIENT : Arreter par le Serveur \n");
    exit(0);
}


void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int main(int argc, char * argv[])
{
   int dp;
   printf("CLIENT : %s\t%d\n", argv[1], getppid());
   dp=open("pipeInitial",O_WRONLY);

   char buffer[BUFFERSIZE] = {};
   
   signal(SIGINT, catchCtrlC);

   //Signal pour voir si on doit stopper le fils
   signal(SIGUSR1, stop);

   while(flag)
   {
      printf("Entre une chaine : \n");
      scanf("%s", buffer); //Permet de tout lire sauf les retours à la ligne

      //sleep(1);
      write(dp, buffer, strlen(buffer)+1 );
   }
   printf("Fin While\n");
//close(dp);
/*
   char buffer[BUFFERSIZE];
    printf("Enter a message: \n");
    while(fgets(buffer, BUFFERSIZE , stdin) != NULL)
    {
      buffer[100] = {};
      fflush(stdin);
      setbuf(stdin, NULL);

        printf("MESSAGE ENTRE : %s\n", buffer);
        write(dp, buffer, strlen(buffer)+1);
        
    }
*/
   close(dp);
   //exit(0);
}