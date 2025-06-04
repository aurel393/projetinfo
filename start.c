//
// Created by apinsell on 12/05/2025.
//

//menu pour choisir le mode de jeu
#include <stdio.h>

int mode(int *size) {
    int choix;
    printf("Quel mode de jeu voulez vous choisir ?\n 1) Test\n 2) Conquete\n 3) Connecte\n");
    scanf("%d",&choix);
    while(choix <1 || choix>3) {
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