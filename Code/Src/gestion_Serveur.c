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

    if (strstr(chaineRecue, "comment") != NULL && strstr(chaineRecue, "blanquette") != NULL)
    {
        printf("Réponse :\tLa blanquette est bonne\n\n");
    }
    else if (strstr(chaineRecue, "dictature") != NULL)
    {
        printf("Réponse :\tUne dictature c'est quand les gens sont communistes, déjà.\n");
        sleep(1);
        printf("Qu'ils ont froid, avec des chapeaux gris et des chaussures à fermeture éclair.\n");
        sleep(1);
        printf("Cest ça, une dictature.\n\n");
    }
    else if (strstr(chaineRecue, "hareng") != NULL && (strstr(chaineRecue, "grand") != NULL || strstr(chaineRecue, "bien") != NULL))
    {
        //On me dit le plus grand bien des harengs pommes à l'huile ?

        printf("Réponse :\tLe patron vous en apportera un ramequin, vous vous ferez une idée.\n\n");
    }
    else if (strstr(chaineRecue, "voiture") != NULL)
    {
        //Jolie voiture ! Dommage qu'elle soit si sale !
        if (strstr(chaineRecue, "sale") != NULL || strstr(chaineRecue, "dommage") != NULL || strstr(chaineRecue, "jolie") != NULL)
        {
            printf("Réponse :\tAh, c’est le moins qu’on puisse dire !\n");
            sleep(2);
            printf("Que j’te trimballe des poules, que j’te trimballe des pastèques !\n\n");
        }
    }
    else if (strstr(chaineRecue, "je") != NULL && strstr(chaineRecue, "suis") != NULL && ((strstr(chaineRecue, "lache") != NULL || strstr(chaineRecue, "lâche"))))
    {

        printf("Réponse :\tTu n'es pas seulement un lâche mais aussi un traitre comme ta petite taille le laissait deviner !\n\n");
    }

    //Tous les allemands ne sont pas Nazis !
    else if (strstr(chaineRecue, "allemands") != NULL)
    {
        if (strstr(chaineRecue, "nazi") != NULL)
        {
            printf("Réponse :\tOui,\n");
            sleep(2);
            printf("je connais cette théorie\n\n");
        }
    }

    else if (strstr(chaineRecue, "shut") != NULL || strstr(chaineRecue, "up") != NULL)
    {
        if (strstr(chaineRecue, "ass") != NULL)
        {
            printf("Réponse :\tD’accord, faisons comme ça, ravi de t’avoir revu l’ami.\n\n");
        }
    }
    //L'idée est que nous travaillons ensemble d'égal à égal
    else if (strstr(chaineRecue, "idée") != NULL || strstr(chaineRecue, "idee") != NULL)
    {
        if (strstr(chaineRecue, "ensemble") != NULL)
        {
            if (strstr(chaineRecue, "égal") != NULL || strstr(chaineRecue, "egal") != NULL)
            {
                printf("Réponse :\tOn en reparlera quand il faudra porter quelque chose de lourd (^o^)\n\n");
            }
        }
    }

    else if (strstr(chaineRecue, "intelligent") != NULL || strstr(chaineRecue, "malin") != NULL || strstr(chaineRecue, "smart") != NULL)
    {
        printf("Réponse :\tNan mais aussi t'abuses là, on te dis de PAS demander si je suis intelligent ou malin\n");
        sleep(5);
        printf("et toi, bien évidement, tu demandes (ノಠ益ಠ)ノ彡┻━┻\n");
        sleep(3);
        printf("Pour qui tu me prends ? Google ? (¬_¬)\n");
        sleep(3);
        printf("Bon en vrai je peux pas t'en vouloir c'est vrai que c'est tentant (^o^)\n\n");
    }
    else
    {
        // On ne détecte pas de mots-clés, on affiche un message explicatif
        printf("C'est impossible pour moi de te répondre, mon intelligence n'est pas assez développée (aucun mot-clé n'a été détecté dans ta question) ¯\\_(ツ)_/¯\n");
    }
}

void printMenuServeur(void)
{
    printf("\n----Bienvenue sur le OSS Akinator----\n\n");
    printf("Tu veux connaitre le nombre de client ?:\t\t\t A\n");
    printf("Pour parler avec les clients:\t\t\t\t\t B\n");
    printf("Tu veux créer un nouveau client ?:\t\t\t\t C\n");
    printf("Une liste de mots-clés, c'est bien non ?:\t\t\t D\n");
    printf("Pour tout quitter \t\t\t\t\t\t Q\n");
    printf("Que choisis-tu ?:\t");
    rewind(stdin); //permet de se positionner au début d'un fichier, ici le flux d'entré
}

void printAvertissementServeur(void)
{
    printf("\nHey, euh oui c'est le serveur qui te parles, avant de commencer, je peux te dire juste un petit mot ?\n");
    sleep(3);
    printf("Les mecs ''brillants'' qui m'on codé on oublié de faire une liste de mot-clés\n");
    sleep(3);
    printf("Donc pour faciliter les choses sache que j'adore les films OSS 117\n");
    sleep(3);
    printf("Si j'ai le début d'une citation, je te donne la réplique suivante du tac au tac\n\n");
    sleep(1);
}

