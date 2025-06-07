#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include <time.h>
#include "board.h"
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


    if (reponse ==1 || reponse == 2)// si on veut jouer une partie : en démarrer une nouvelle ou en charger une
    {
        if (reponse ==1) //quand on veut commmencer une nouvelle partie
        {
            modejeu = mode(s); //récupère le mode de jeu et la taille du plateau si l'utilisateur a choisi de jouer
            user = rand()%2; //défini aléatoirement quel joueur commmence
            p.taille = size;
            initialiser_plateau(&p);
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
            return 0;
            }
        //if (modejeu == 2)

    }
    else if (reponse == 3)
    {
        printf("Au revoir !\n");
        return 0; //si l'utilisateur a choisi de quitter, on sort du programme
    }
    return 0;
}