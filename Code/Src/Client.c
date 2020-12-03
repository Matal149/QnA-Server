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


/*

int main(int argc, char * argv[])
{
   printf("CLIENT : %s\t%d\n", argv[1], getppid());
    sleep(10);
    exit(0);
}

*/




/*
int main(void)
{
    int des;
    int buf;

	printf("\nDANS LE CLIENT\n" );
    des=open("pipe",O_RDONLY);
    read(des,&buf,sizeof(int));
    printf("%d", buf);


    close(des);

    return 0;
}
*/

/*
int check_for_EOF()
{
    if (feof(stdin))
    {
       return 1;
    }

    int c = getc(stdin);

    if (c == EOF)
    {
       return 1;
    }

    ungetc(c, stdin);
}
*/

#define BUFFERSIZE 100

int flag = 1;


void catchCtrlC()
{
   flag = 0;
   printf("passe ctrl C\n");
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
   dp=open("pipe",O_WRONLY);

   char buffer[BUFFERSIZE] = {};
   
   signal(SIGINT, catchCtrlC);

   while(flag)
   {
      //char buffer[BUFFERSIZE] = {};
      printf("Entre une chaine : \n");
      scanf("%s", buffer); //Permet de tout lire sauf les retours à la ligne

      //getchar();

      sleep(5);
      write(dp, buffer, strlen(buffer)+1 );
      
      //buffer[BUFFERSIZE] = {};
      
      //fflush(stdin);
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