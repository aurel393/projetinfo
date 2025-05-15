#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "start.h"
#include <time.h>

int main(void) {
    srand(time(0));
    int reponse,size,user;
    int *s = &size;//pointeur pour récupérer la taille du plateau
    reponse= menu(); //demande à l'utilisateur son choix
    if (reponse ==1) reponse = mode(s);//récupère le mode de jeu et la taille du plateau si l'utilisateur a choisi de jouer
    user= rand()%2 +1;
    test;

    printf("%d %d %d", reponse, *s,user);//test


    return 0;
}
