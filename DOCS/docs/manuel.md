Manuel utilisateur
====================
>	Cette page est consacrée à l'explication des fonctionnalités de l'application
>	Il s'articule en trois partie
> > * Lancement de l'application
> > * Fonctionnalités du serveur
> > * Fonctionnalités des clients

Lancement de l'application
---------------------

> Pour lancer l'application, vous devez lancer l'éxecutable **Serveur**
> >	* Pour ce faire, déplacez vous dans le sous-dossier **Bin** au moyen de la commande suivante :

```sh
# Depuis la racine du projet
cd Code/Bin/
```
> Après, toujours dans votre terminal, entrez la commande
```sh
# Depuis le sous dossier Bin

./Serveur 2 test

# Explication de la commande
#	./Serveur : nom de l'éxecutable à lancer.
#	2 : nombre de clients, lancés dès le démarrage initial de l'application,
#		vous pouvez en mettre autant que vous le souhaitez.
#	test : nom du pipe avec lequel le serveur et les clients vont parler durant cette session, 
#		   effectif jusqu'à ce que l'utilisateur quitte l'application.
```
> 
> 
> 
> 
> ## Fonctionnalités du serveur
> Présentation des fonctionnalités du serveur

> Dans le terminal représentant le serveur, vous serez acceulli avec avec le menu suivant :

>	* Connaître le nombre de clients
> >	Le choix **"Tu veux connaitre le nombre de client ?: ______________ A"**
> >	
> >	Permet, en appuyant sur '**A**', de connaître le nombre de clients pouvant être gérés par le serveur pour la session courante

>	* Communiquer avec les clients
> >	Le choix **"Pour parler avec les clients: ______________ B"**
> >	
> >	Permet, en appuyant sur '**B**', d'entrer dans une routine d'écoute des clients, ainsi nous pouvons voir les questions posées par les clients et afficher les réponses

>	* Créer un nouveau client
> >	Le choix **"Tu veux créer un nouveau client ?: ______________ C"**
> >	
> >	Permet, en appuyant sur '**C**', de créer un nouveau client pouvant être géré par le serveur


>	* Connaître les mots-clés détectables par le serveur
> >	Le choix **"Une liste de mots-clés, c'est bien non ?: ______________ D"**
> >	
> >	Permet, en appuyant sur '**D**', d'afficher une liste de mots-clés, s'ils sont présents dans les questions posées par les clients, le serveur pourra les détecter et répondre de manière adéquate.

>
>


> ## Fonctionnalités des clients
> Présentation des fonctionnalités des clients

>	* Questionner le serveur
> >	Le choix **"Questionner le serveur ______________ 1"**
> >	
> >	Permet, en appuyant sur '**1**', de poser une question au serveur, qu'il traitrera, et répondra.



>	* Quitter le client courant
> >	Le choix **"Pour parler avec les clients: ______________ 0"**
> >	
> >	Permet, en appuyant sur '**0**', de quitter le client courant 
>
>
