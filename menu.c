//
// Created by apinsell on 12/05/2025.
//
#include <stdio.h>

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