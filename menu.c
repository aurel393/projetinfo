//
// Created by apinsell on 12/05/2025.
//
#include <stdio.h>
#include "board.h"
#include "menu.h"

int menu() {
    int rep,rep2;
    printf("-----------Menu-----------\n 1) Demarrer une partie\n 2) Reprendre une partie\n 3) Quitter\n"); //affichage du menu
    scanf("%d", &rep);
    while(rep <1 || rep>3) {
        printf("Veuillez entrer votre choix: 1,2 ou 3\n"); //message d'erreur
        scanf("%d", &rep);
    }
    return rep;
}

int mode(int *size) {
    int choix;
    printf("Quel mode de jeu voulez vous choisir ?\n 1) Conquete\n 2) Connecte\n");
    scanf("%d",&choix);
    while(choix <1 || choix>2) {
        printf("Veuillez entrer votre choix: entre 1 et 3\n"); //message d'erreur
        scanf("%d", &choix);
    }
    printf("Quelle taille d'echiquier voulez-vous ?\n (entre 6x6 et 12x12)\n");
    scanf("%d", size);
    while(*size <6 || *size>12) {
        printf("Veuillez entrer votre choix entre 6 et 12\n"); //message d'erreur
        scanf("%d", size);
    }
    return choix;
}

int menu_jeu(Joueur j){
    int rep;
    if (j==1) printf("C'est au tour des blancs\n");
    else printf("C'est au tour des noirs\n");

    printf("Que voulez vous faire ? \n");
    printf("1) Poser une pièce \n");
    printf("2) Abandonner \n");
    printf("3) Sauvegarder la partie \n");
    scanf("%d", &rep);
    while (rep <1 || rep>3)
    {
        printf("Veuillez entrer votre choix: 1,2 ou 3\n");
        scanf("%d", &rep);
    }
    if (rep == 3) printf("Sauvegarde en cours...\n");
    //fonction de sauvegarde
    return rep;
}
