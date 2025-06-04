//
// Created by aurel on 22/05/25.
//
#include <stdio.h>
#include "board.h"
#include "compteur.h"

void initialiser_compteur(CompteurPiece *cp)//met le compteur avec les bonnes pièces pour chaque joueur
{
    cp->compt[PION] = 8;
    cp->compt[TOUR] = 2;
    cp->compt[CAVALIER] = 2;
    cp->compt[FOU] = 2;
    cp->compt[DAME] = 1;
    cp->compt[ROI] = 1;
}

int compteur(CompteurPiece *cp, TypePiece p)
{
    if (cp->compt[p] > 0)
    {
        cp->compt[p] --;
        return 0;
    }
    return -1;
}
