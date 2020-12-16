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


int nb_clients; //Ajout d'une variable permettant de stocker le nb de clients


void traitementChaineRecue(char *chaineRecue);

void printMenuServeur(void);

void printAvertissementServeur(void);

void stoperLecture();



