//
// Created by aurel on 19/05/25.
//
//menu une fois que l'on est dans une partie

#include <stdio.h>
#include "game.h"

#include "board.h"

int menu_jeu(Joueur j){
    int rep;
    if (j==BLANC) printf("C'est au tour des blancs\n");
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

