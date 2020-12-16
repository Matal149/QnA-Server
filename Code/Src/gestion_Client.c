#include "gestion_Client.h"


void catchCtrlC()
{
   flag_Client = 0;
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


void printMenuClient(void)
{
   printf("\n\tHello jeune client entrepreneur");
   printf("\n\nQuestionner le serveur............: 1\n");
   printf("Pour quitter le client.......................: 0\n");
   printf("Que choisis-tu ?: ");
   rewind(stdin); //permet de se positionner au début d'un fichier, ici le flux d'entré
}
