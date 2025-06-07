//tout ce qui gère le plateau: structures des pièces et fonctions comme afficher, initialiser, convertir...

#include <stdio.h>
#include "board.h"

#include <string.h>



void initialiser_plateau(Plateau* p)
{
    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            p->cases[i][j] = strdup(". ");
        }
    }
}

//La fonction suivante prends le type de la pièce (fou, cavalier...) et le joueur pour avoir la couleur
//afin de faire correspondre le symbole au type de pièce et au joueur.

void definir_symbole(Piece* p) {
    if (p->type >= 0 && p->type < 6 && p->joueur >= 0 && p->joueur <= NOIR) {//test de vérification
        // Copie la chaîne de symbole Unicode correspondante dans p->symbole
        strcpy(p->symbole, symboles[p->joueur][p->type]);
    } else {
        // En cas de valeur invalide, on met un symbole générique
        strcpy(p->symbole, "?");
    }
}




//Cette fonction convertis la chaine de caractere entrée par l'utilisateur en enum
TypePiece conversion_type(const char* saisie) {
    if (strcmp(saisie, "pion") == 0) return PION;
    if (strcmp(saisie, "tour") == 0) return TOUR;
    if (strcmp(saisie, "cavalier") == 0) return CAVALIER;
    if (strcmp(saisie, "fou") == 0) return FOU;
    if (strcmp(saisie, "dame") == 0) return DAME;
    if (strcmp(saisie, "roi") == 0) return ROI;
    return -1; // Invalide
}

Joueur conversion_joueur(int j1) { // convertis un int du joueur en enum pour aller dans la structure
    if (j1 == 1) return NOIR;
    else return BLANC;
}



void afficher_plateau(Plateau p) {
    for (int i = 0; i < p.taille; i++) {
        for (int j = 0; j < p.taille; j++) {
            printf("%s ", p.cases[i][j]);
        }
        printf("\n");
    }
}


const char* symboles[2][6] = {
    // JOUEUR1 (noir)
    { "♙ ", "♖ ", "♘ ", "♗ ", "♕ ", "♔ " },
    // JOUEUR2 (blanc)
    { "♟ ", "♜ ", "♞ ", "♝ ", "♛ ", "♚ " }
};
