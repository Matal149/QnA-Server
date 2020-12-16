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

#include "gestion_Serveur.h"

//volatile int stopLecture = 1;
char KEYWORDS_LIST[1000] = {"comment, blanquette, dictature, hareng, grand, bien, voiture, sale, dommage, jolie, je, suis, lache, allemands, nazis, shut, up, ass, idee, ensemble, égal, intelligent, malin, smart"};


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

    printAvertissementServeur();

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

            printMenuServeur();
            scanf(" %c", &choixPere);
            getchar();

            switch (choixPere)
            {
            case 'A':
            case 'a':
                printf("En ce moment il y a %d clients\n", nb_clients);
                break;

            case 'C':
            case 'c':
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

            case 'B':
            case 'b':
                if (pid == 0)
                {
                    //C'est les clients qui gèrent les actions ici
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
                        printf("ALLO ?\n");
                        sleep(2);
                        printf("Ah mais en fait ya plus personne a qui parler !\n");
                    }
                }
                close(desc);
                break;

            case 'D':
            case 'd':
                printf("\nVoici une bien belle liste de mots-clés\n");
                printf("%s", KEYWORDS_LIST);
                printf("\n");
                break;

            case 'Q':
            case 'q':
                printf("\nJ'attend la fermeture des clients et me ferme\nCiao à une prochaine fois\n");
                kill(0, SIGTERM); //SIGTERM permet de terminer proprement un process
                                  // cf https://korben.info/commande-kill-linux-tuer-processus.html + signal.h l.112
                wait(NULL);
                return 0;
                break;

            default:
                printf("J'ai pas compris ce que tu me demandes, entre une commande (magique) correcte\t(ノ°∀°)ノ⌒･*:.｡. .｡.:*･゜ﾟ･*☆\n");
                break;
            }
        } while (1);
    }
    //fin boucle
    //printf("FIN Programme\n");
    close(desc);
    wait(NULL);

    exit(0);
}
