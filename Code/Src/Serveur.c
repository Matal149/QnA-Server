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

#include <ctype.h>

#define TAILLE_MAX_CHAINE 100


volatile int stopLecture = 1;

void stoperLecture()
{
    stopLecture = 0;
}

//converti la chaine de caracteres en minuscules
char* toLower(char* s)
{
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}



//Vérification par mots-clés et affichage de la réponse
void traitementChaineRecue(char * chaineRecue)
{
    //conversion de la chaine en minuscile pour faciliter le traitement
    //char chaineMinuscule[TAILLE_MAX_CHAINE];
    chaineRecue = toLower(chaineRecue);

    if(strstr(chaineRecue, "oui") != NULL || strstr(chaineRecue, "non") != NULL || strstr(chaineRecue, "ah") != NULL)
    {
        printf("E Y E S, e-yes\n");
    }
    else if(strstr(chaineRecue, "yes") != NULL || strstr(chaineRecue, "nope") != NULL || strstr(chaineRecue, "geh") != NULL)
    {
        printf("Y U geh ?\n");
    }
    else
    {
        // On ne détecte pas de mots-clés 
        printf("Il nous est impossible pour le moment de vous répondre, l'intelligence de notre serveur n'est pas encore assez développée :(\n");
    }
    
}

int main(void)
{
    int pid,desc,nb ;
    char chaineRecue[TAILLE_MAX_CHAINE];

    //Création du pipe initial, 
    unlink("pipeInitial");
    mkfifo("pipeInitial" ,0666);

    //int stopLecture = 1;
    
    //Association du 
    signal(SIGCHLD, stoperLecture);

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
            printf("Message reçu du client : '%s'\n ",chaineRecue);

            //Vérification si chaine reçue contient "fermer" ou "quitter"
            if(strstr(chaineRecue, "quitter") == NULL)
            {
                //traitement des sous chaines suivant mot clés
                traitementChaineRecue(chaineRecue);
            }
            else 
            {
                stopLecture = 0;

                //Arret du Client
                kill(pid,SIGUSR1);
            }
                //Arret de la lecture infinie
                //stopLecture = stopLecture();
            printf("stopLecture : %d\n", stopLecture);
        }
        
    }
//fin boucle        
        printf("FIN Programme apres boucle StopLecture\n");
        close(desc);
        wait(NULL);

        exit(0);
}

