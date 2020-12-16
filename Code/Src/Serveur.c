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

int nb_clients; //Ajout d'une variable permettant de stocker le nb de clients

void stoperLecture()
{
    //stopLecture = 0;
    nb_clients--; //On vient de recevoir le signal de mort d'un client, on enlève 1 au nb de clients
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

    //Création du pipe initial,
    unlink(argv[2]);
    mkfifo(argv[2], 0666);

    //int stopLecture = 1;

    //Association du
    signal(SIGCHLD, stoperLecture);

    //pid = fork();
    /*
    if (pid == 0)
    { //on lance le programme de créatio nde clients
        printf("\nInvocation d'un CLIENT\n");
        execl("/usr/bin/xterm", "xterm", "-e", "./Client", argv[2], "Client", NULL);
    }
    */

    //Au lieu de créer un seul fork pour un seul client on doit en créer un pour chaque clientdemander, on utilise une boucler
    nb_clients = atoi(argv[1]); //Conversion du nombre passé en argument en entier
    for (int i = 0; i < nb_clients; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            execl("/usr/bin/xterm", "xterm", "-e", "./Client", argv[2], "Client", NULL);
        }
    }

    if (pid == 0)
    {
        //Il n'y a rien a faire
    }
    else
    {
        desc = open(argv[2], O_RDONLY); //On ouvre le pipe en lecture uniquement

        do
        {

            printMenuPere();
            scanf(" %c", &choixPere);
            getchar();

            switch (choixPere)
            {
            case '1':

                break;

            case '3':
                printf("Invocation d'un nouveau client\n");

                if (pid > 0)
                {
                    pid = fork();
                    if (pid == 0)
                    {
                        execl("/usr/bin/xterm", "xterm", "-e", "./Client", argv[2], "Client", NULL);
                    }
                }
                printf("Le nouveau client est prêt (a pas faire énormément de choses XD)\n");
                nb_clients++; //On  ajoute 1 au nombre total de clients en cours
                break;

            case '2':
                if (pid == 0)
                {
                    //Serveur
                }
                else
                {
                    desc = open(argv[2], O_RDONLY);
                    if (nb_clients != 0) //Ajout de la condition pour vérifier la présence de clients, on ne lit pas en permanence s'il n'y a personne avec qui communiquer
                    {
                        while (nb_clients > 0) //On lit en permanence les données reçues envoyées par les clients
                        {
                            nb = read(desc, chaineRecue, TAILLE_MAX_CHAINE);
                            chaineRecue[nb] = '\0';
                            if (nb != 0)
                            {
                                printf("Lecture : %s \n", chaineRecue);
                                if (strstr(chaineRecue, "Quitter") == NULL)
                                {
                                    traitementChaineRecue(chaineRecue);
                                }
                            }
                        }
                    }
                    else //On a personne avec qui communiquer
                    {
                        printf("Hey ya plus personne a qui parler, pour un dialogue faut deux non?\n");
                    }
                }
                close(desc);
                break;

            default:
                break;
            }
        } while (1);
    }
    //fin boucle
    printf("FIN Programme\n");
    close(desc);
    wait(NULL);

    exit(0);
}

void printMenuPere(void)
{
    printf("\n\tBienvenue sur le Akinator du pauvre\n");
    printf("Tu veux connaitre le nombre de client ?:\t\t\t 1\n");
    printf("Pour parler avec les clients:\t\t\t\t\t 2\n");
    printf("Tu veux créer un nouveau client ?:\t\t\t\t 3\n");
    printf("Pour tout quitter \t\t\t\t\t\t\t 0\n");
    printf("Ton choix: ");
    rewind(stdin); //permet de se positionner au début d'un fichier, ici le flux d'entré
}
