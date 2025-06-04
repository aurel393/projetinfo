#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "start.h"
#include <time.h>
#include "board.h"
#include "gametest.h"
#include "sauvegarde.h"
#include "conquete.h"


int main(void) {
    srand(time(0));

    int reponse,size,user,modejeu;
    int *s = &size; //pointeur pour récupérer la taille du plateau
    Plateau p;
    FILE *save;
    CompteurPiece cpj1,cpj2;

    reponse= menu(); //demande à l'utilisateur son choix


    if (reponse ==1 || reponse == 2)// si on veut jouer une partie : en démarrer une nouvelle ou en charger une
    {
        if (reponse ==1) //quand on veut commmencer une nouvelle partie
        {
            modejeu = mode(s); //récupère le mode de jeu et la taille du plateau si l'utilisateur a choisi de jouer
            user = rand()%2; //défini aléatoirement quel joueur commmence
            p.taille = size;
        }
        else chargement(&p, &user, &modejeu, &cpj1,&cpj2); //quand on veut charger une partie
        
        if (modejeu ==1) gametest(&p,user);
        //if (modejeu == 2) conquete(&p,user);
        //if (modejeu == 3) connecte(&p,user);

    }
    else if (reponse == 3)
    {
        printf("Au revoir !\n");
        return 0; //si l'utilisateur a choisi de quitter, on sort du programme
    }
    return 0;
}