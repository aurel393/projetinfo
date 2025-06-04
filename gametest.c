//
// Created by aurel on 21/05/25.
//
//premier test pour poser les pièces

#include "gametest.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"
#include "game.h"
#include "conquete.h"

void gametest(Plateau *p, int j1)
{
    Piece piece1;
    Position pos1;
    TypePiece t = -1;
    Joueur j=conversion_joueur(j1);
    char saisie[10];
    int etat_partie=menu_jeu(j),mode=0;
    CompteurPiece cpj1,cpj2;

    initialiser_plateau(p);
    afficher_plateau(*p);
    initialiser_compteur(&cpj1);
    initialiser_compteur(&cpj2);


    while (etat_partie == 1) //reste dans le jeu tant que l'on veut continuer à jouer
    {
        while (t == -1) {
        printf("Quel pièce voulez vous placer ? \n");
        scanf("%9s", saisie);  // lis une chaîne de 9 caracteres + \0

        t = conversion_type(saisie);//retourne l'enum correspondant à la chaine de caractere
        }

        piece1.type = t;
        piece1.joueur = j;

        definir_symbole(&piece1); //conversion du type de piece en symbole unicode

        do {
            printf("Entrez la ligne (1 à %d) : ", p->taille);
            scanf("%d", &pos1.ligne);
        } while (pos1.ligne < 1 || pos1.ligne > p->taille);

        do {
            printf("Entrez la colonne (1 à %d) : ", p->taille);
            scanf("%d", &pos1.colonne);
        } while (pos1.colonne < 1 || pos1.colonne > p->taille);

        // Mise à jour du plateau
        strcpy(p->cases[pos1.ligne - 1][pos1.colonne - 1], piece1.symbole);
        deplacement(p,piece1,pos1);

        // Affichage
        afficher_plateau(*p);

        //refais un tour
        etat_partie = menu_jeu(j);

        if (j==BLANC) j=NOIR;
        else j=BLANC;
        t = -1;


    }
    if (etat_partie == 2)
    {
        if (j==0) j=2;
        printf("Fin de partie ! le jouer %d gagne !\n",j);
    }
    if (etat_partie == 3)
    {
        sauvegarde("save.txt",p,j1,mode,cpj1,cpj2);
    }
}
