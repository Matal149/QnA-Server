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

#define TAILLE_MAX_CHAINE 100

int stopLecture()
{

}


int main(void)
{
    int pid,desc,nb ;
    char chaineRecue[TAILLE_MAX_CHAINE];

    //Création du pipe initial, 
    unlink("pipeInitial");
    mkfifo("pipeInitial" ,0666);

    int stopLecture = 1;

    pid=fork();

    if(pid == 0)
    {
        printf("\nEXECUTION CLIENT\n" );
        execl("/usr/bin/xterm" , "xterm", "-e", "./Client", "Client", NULL);
    }
    else
    {
        desc=open("pipeInitial",O_RDONLY);

//boucler ici
    while(stopLecture == 1)
    {
        nb=read(desc,chaineRecue,TAILLE_MAX_CHAINE);
        chaineRecue[nb] = '\0';
        printf(" message reçu du client : %s\n ",chaineRecue);

        //Vérification si chaine reçue contient "fermer" ou "quitter"
        if(strstr(chaineRecue,"fermer") == NULL || strstr(chaineRecue, "quitter") == NULL)
        {
            //traitement des sous chaines suivant mot clés 
        }
        else
        {
            stopLecture = 0;
        }
        
    }
//fin boucle        
        
        close(desc);
        wait(NULL);
    }

    
  exit(0);
}