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

#include "gestion_Client.h"

int main(int argc, char *argv[])
{
   int dp;

   char choixFils;

   int bclFermetureClient = 1; //On déclare une varialbe permlettant de boucler à l'infini tant qu'on a pas effectuer la bonne conbinaison de touches (ctrl+D)

   printf("CLIENT : %s\t%d\n", argv[1], getppid());
   dp = open(argv[1], O_WRONLY);

   printf("ouverture PIPE : %s\n", argv[1]);

   char buffer[BUFFERSIZE] = {};
   //char stockClientPID2[BUFFERSIZE] = {};

   int pid_client = getpid();

   signal(SIGINT, catchCtrlC);

   //Signal pour voir si on doit stopper le fils
   signal(SIGUSR1, stop);
   /*
   while(flag_Client)
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
      printMenuClient();
      scanf("%c", &choixFils);
      getchar();
      switch (choixFils)
      {
      case '0':
         dp = open(argv[1], O_WRONLY);
         char quitterClient[BUFFERSIZE] = "Quitter "; //On stocke qu'on quitte, avec le mot-clé "quitter"
         //strcat(quitterClient, "Quitter ");
         char stockClientPID[BUFFERSIZE] = {};
         sprintf(stockClientPID, "%d", getpid()); //On rajoute le pid pour savoir quel client on quitte
         strcat(quitterClient, stockClientPID);   //On concaténe les deux chaines de caractères
         printf("%s", quitterClient);
         write(dp, quitterClient, strlen(quitterClient) + 1); // on écrit sur le pipe
         close(dp);
         printf("\nQuittage du pipe avec ce client %d\n", getpid());
         while (bclFermetureClient == 1) //On boucle tant que l'utilisateur n'a pas entrer la commande Ctrl+D
         {
            printf("Un  petit Ctrl+D pour quitter le client ?\n");
            char bufDetectCtrlD[1];

            if (fgets(bufDetectCtrlD, 10, stdin) == NULL)
            {
               bclFermetureClient = 0; //On change la valeur de la variable, pour arreter la boucle
            }
            else
            {
               printf("Bon faudrait saisir la bonne commande pour quitter\nJe t'aide un peu (^o^) (Ctrl+D)");
            }
         }

         printf("Fermeture du client %d\n", getpid());
         exit(0);
         break;

      case '1':
         dp = open(argv[1], O_WRONLY); // Ouverture du pipe
         
         char stockClientPID2[BUFFERSIZE] = {};
         strcat(stockClientPID2, "Msg envoyé par : ");
         sprintf(stockClientPID2, "%d", getpid()); //On rajoute le pid pour savoir quel client on quitte
         strcat(stockClientPID2, "  ");

         char demande_client[BUFFERSIZE] = {};
         strcpy(demande_client, stockClientPID2);
         //sprintf(demande_client, "%s", stockClientPID2);
         //sprintf(demande_client, "%s", stockClientPID2);
         printf("Tu veux demander quoi à \"Akinator\" du pauvre ? (⌐■_■):\n");
         scanf(" %[^\n]", buffer); //Ne bloque pas au premier espace rencontré
         //scanf("%s", buffer); //Bloque au premier espace rencontré
         strcat(demande_client, buffer);
         getchar();

         
         write(dp, demande_client, strlen(demande_client) + 1);

         sleep(1);
         close(dp);
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
