#!/bin/bash
echo "Compilation des sources et génération des binaires correspondant"
gcc Client.c gestion_Client.h gestion_Client.c -o ../Bin/Client
gcc Serveur.c gestion_Serveur.c gestion_Serveur.h -o ../Bin/Serveur
echo " "
echo "Compilation terminée"