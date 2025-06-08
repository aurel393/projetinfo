#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include <time.h>
#include "board.h"
#include "connecte.h"
#include "sauvegarde.h"
#include "conquete.h"


int main(void) {
    srand(time(0));
    int reponse,size,user,modejeu;
    int *s = &size;
    Plateau p;
    FILE *save;
    CompteurPiece cpj1,cpj2;

    reponse= menu(); //demande à l'utilisateur son choix


    if (reponse !=3)// si on veut jouer une partie : en démarrer une nouvelle ou en charger une
    {
        if (reponse ==1) //quand on veut commmencer une nouvelle partie
        {
            modejeu = mode(s); //récupère le mode de jeu et la taille du plateau si l'utilisateur a choisi de jouer
            user = rand()%2; //défini aléatoirement quel joueur commmence
            p.taille = size;
            initialiser_plateau(&p);
            initialiser_tableau_capture(&p);
            initialiser_compteur(&cpj1);
            initialiser_compteur(&cpj2);
        }
        else
        {
            chargement(&p, &user, &modejeu, &cpj1,&cpj2); //quand on veut charger une partie
            afficher_plateau(p);
        }
        if (modejeu ==1)
            {
            conquete(&p,user, cpj1, cpj2);
            }
        if (modejeu == 2)
        {
            connecte(&p,user,cpj1,cpj2);
        }

    }
    else
    {
        printf("Au revoir !\n");
        return 1; //si l'utilisateur a choisi de quitter, on sort du programme
    }
    return 0;
}