//
// Created by apinsell on 12/05/2025.
//
#include <stdio.h>

int mode(int *size) {
    int choix;
    printf("Quel mode de jeu voulez vous choisir ?\n 1) Conquete\n 2) Connecte\n");
    scanf("%d",&choix);
    while(choix <1 || choix>2) {
        printf("Veuillez entrer votre choix: 1 ou 2\n"); //message d'erreur
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