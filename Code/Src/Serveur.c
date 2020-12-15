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

void printMenuPere(void);

void stoperLecture()
{
    stopLecture = 0;
}

//converti la chaine de caracteres en minuscules
char *toLower(char *s)
{
    for (char *p = s; *p; p++)
        *p = tolower(*p);
    return s;
}

////Fonction qui traite les chaines de caractères reçues des clients. Vérification par mots-clés et affichage de la réponse
void traitementChaineRecue(char *chaineRecue)
{
    //conversion de la chaine en minuscile pour faciliter le traitement
    //char chaineMinuscule[TAILLE_MAX_CHAINE];
    chaineRecue = toLower(chaineRecue);

    if (strstr(chaineRecue, "oui") != NULL || strstr(chaineRecue, "non") != NULL || strstr(chaineRecue, "ah") != NULL)
    {
        printf("E Y E S, e-yes\n");
    }
    else if (strstr(chaineRecue, "yes") != NULL || strstr(chaineRecue, "nope") != NULL || strstr(chaineRecue, "geh") != NULL)
    {
        printf("Y U geh ?\n");
    }
    else if (strstr(chaineRecue, "intelligent") != NULL || strstr(chaineRecue, "malin") != NULL || strstr(chaineRecue, "smart") != NULL)
    {
        printf("Nan mais aussi t'abuses là, on te dis de PAS demander si je suis intelligent ou malin\n");
        sleep(5);
        printf("et toi, bien évidement, tu demandes (ノಠ益ಠ)ノ彡┻━┻\n");
        sleep(3);
        printf("Pour qui tu me prends ? Google ? (¬_¬)\n");
        sleep(3);
        printf("Bon en vrai je peux pas t'en vouloir c'est vrai que c'est tentant (^o^)\n");
    }
    else
    {
        // On ne détecte pas de mots-clés, on affiche un message explicatif
        printf("Il nous est impossible pour le moment de vous répondre, l'intelligence de notre serveur n'est pas encore assez développée (aucun mot-clé n'a été détecté dans votre question) ¯\\_(ツ)_/¯\n");
    }
}

int main(int argc, char *argv[])
{
    int pid, desc, nb;
    char chaineRecue[TAILLE_MAX_CHAINE];

    char choixPere; //Permet de stocker le choix dans le menu du serveur
    int nb_clients;

    //Création du pipe initial,
    unlink(argv[1]);
    mkfifo(argv[1], 0666);

    //int stopLecture = 1;

    //Association du
    signal(SIGCHLD, stoperLecture);

    pid = fork();

    if (pid == 0)
    { //on lance le programme de créatio nde clients
        printf("\nEXECUTION CLIENT\n");
        execl("/usr/bin/xterm", "xterm", "-e", "./Client", argv[1], "Client", NULL);
    }
    else
    {
        while (1)
        {
            desc = open(argv[1], O_RDONLY);

            printMenuPere();
            scanf(" %c", &choixPere);
            getchar();

            switch (choixPere)
            {
            case '1':

                break;

            case '3':
                printf("Creation d'un nouveau fils\n");

                if (pid > 0)
                {
                    pid = fork();
                    if (pid == 0)
                    {
                        //on lance le programme de créatio nde clients
                        execl("/usr/bin/xterm", "xterm", "-e", "./Client", argv[1], "Client", NULL);
                    }
                }
                printf("Le nouveau client est prêt\n");
                break;

            case '2':
                while (stopLecture == 1)
                {
                    nb = read(desc, chaineRecue, TAILLE_MAX_CHAINE);
                    chaineRecue[nb] = '\0';
                    printf("Message reçu du client : '%s'\n ", chaineRecue);

                    //Vérification si chaine reçue contient "fermer" ou "quitter"
                    if (strstr(chaineRecue, "quitter") == NULL)
                    {
                        //traitement des sous chaines suivant mot clés
                        traitementChaineRecue(chaineRecue);
                    }
                    else
                    {
                        stopLecture = 0;

                        //Arret du Client
                        kill(pid, SIGUSR1);
                    }
                    //Arret de la lecture infinie
                    printf("stopLecture : %d\n", stopLecture);
                }
                break;

            default:
                break;
            }
        }
    }
    //fin boucle
    printf("FIN Programme apres boucle StopLecture\n");
    close(desc);
    wait(NULL);

    exit(0);
}

void printMenuPere(void)
{
    printf("\n\tBienvenue sur le Akinator du pauvre\n");
    printf("Tu veux connaitre le nombre de client ?:\t\t\t 1\n");
    printf("Pour parler avec les clients:\t\t\t 2\n");
    printf("Tu veux créer un nouveau client ?:\t\t\t 3\n");
    printf("Pour tout quitter \t\t\t 0\n");
    printf("Ton choix: ");
    rewind(stdin); //permet de se positionner au début d'un fichier, ici le flux d'entré
}
