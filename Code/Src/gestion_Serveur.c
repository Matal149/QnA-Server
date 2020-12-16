#include "gestion_Serveur.h"




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




void printMenuServeur(void)
{
    printf("\n\tBienvenue sur le Akinator du pauvre\n");
    printf("Tu veux connaitre le nombre de client ?:\t\t\t A\n");
    printf("Pour parler avec les clients:\t\t\t\t\t B\n");
    printf("Tu veux créer un nouveau client ?:\t\t\t\t C\n");
    printf("Pour tout quitter \t\t\t\t\t\t\t Q\n");
    printf("Ton choix: ");
    rewind(stdin); //permet de se positionner au début d'un fichier, ici le flux d'entré
}