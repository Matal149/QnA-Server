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

void printMenuFils(void);

void catchCtrlC()
{
   flag = 0;
   printf("passe ctrl C\n");
}

void stop(int sig)
{
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

int main(int argc, char *argv[])
{
   int dp;

   char choixFils;

   int bclFermetureClient = 1; //On déclare une varialbe permlettant de boucler à l'infini tant qu'on a pas effectuer la bonne conbinaison de touches (ctrl+D)

   printf("CLIENT : %s\t%d\n", argv[1], getppid());
   dp = open(argv[1], O_WRONLY);

   printf("ouverture PIPE : %s\n", argv[1]);

   char buffer[BUFFERSIZE] = {};

   signal(SIGINT, catchCtrlC);

   //Signal pour voir si on doit stopper le fils
   signal(SIGUSR1, stop);
   /*
   while(flag)
   {
      printf("Entre une chaine : \n");
      scanf("%s", buffer); //Permet de tout lire sauf les retours à la ligne

      //sleep(1);
      write(dp, buffer, strlen(buffer)+1 );
   }
   printf("Fin While\n");
*/

   while (1) //on boucle à l'infini
   {
      printMenuFils();
      scanf("%c", &choixFils);
      getchar();
      switch (choixFils)
      {
      case '0':
         //dp=open(arg[1],O_WRONLY);
         //strcat(fermeture,Cpid);
         //write(dp, fermeture,250);
         close(dp); // On ferme le pipe
         printf("Fermeture du pipe\n");
         while (bclFermetureClient == 1)
         {
            printf("Appuyer sur CTR+D pour fermer le client\n");
            char buffer[1];

            if (fgets(buffer, 10, stdin) == NULL)
            {
               bclFermetureClient = 0;
            }
            else
            {
               printf("Saisi la bonne commande pour quitter\nJe t'aide un peu Ctrl+D (^o^)");
            }
         }

         printf("Fermeture du fils\n");
         exit(0);
         break;

      case '1':
         printf("Tu veux demander quoi à Akinator du pauvre ? (⌐■_■):\n");
         //scanf(" %[^\n]",question);
         scanf("%s", buffer);
         getchar();

         //strcat(question,"\t");   //Ajout d'un caractere de séparation
         //strcat(question,Cpid);		// On ajoute le pid a fin de la question

         dp = open(argv[1], O_WRONLY); // Ouverture du PIPE puis ecriture de la question
         //nbcarecrit = write(dp, question,sizeof(question));
         write(dp, buffer, strlen(buffer) + 1);

         sleep(1);  // Tempo d'une seconde
         close(dp); // Fermeture du PIPE
         break;

      default:
         printf("J'ai pas compris ce que tu me demandes, entre une commande (magique) correcte\t(ノ°∀°)ノ⌒･*:.｡. .｡.:*･゜ﾟ･*☆\n");
         break;
      }
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
   //close(dp);
   //exit(0);
}

void printMenuFils(void)
{
   printf("\n\tHello jeune client entrepreneur");
   printf("\n\nQuestionner le serveur............: 1\n");
   //printf("Liste des mots clés...........: 2\n");
   printf("Pour quitter le client.......................: 0\n");
   printf("Ton choix: ");
   rewind(stdin); //permet de se positionner au début d'un fichier, ici le flux d'entré
}