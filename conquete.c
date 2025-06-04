//
// Created by aurel on 22/05/25.
//

#include "conquete.h"
#include <stdio.h>
#include "board.h"
#include <string.h>

void conquete(Plateau *p, int j1)
{

}


int deplacement(Plateau *p, Piece piece, Position position)
{
    int i = position.ligne -1;
    int j = position.colonne-1;

    switch (piece.type)
    {
        case PION:
            {
                if (piece.joueur == BLANC)
                {

                }
                else
                {

                }
            };

        case TOUR:
            {
                while (i>0)
                {
                    if (strcmp(p->cases[i-1][j],".") == 0 || strcmp(p->cases[i-1][j],"⬛") == 0 || strcmp(p->cases[i-1][j],"⬜")==0)
                    {
                        if (piece.joueur == BLANC) strcpy(p->cases[i-1][j],"⬜");
                        else strcpy(p->cases[i-1][j] ,"⬛");
                        i--;
                    }
                    else i=0;
                }
                i = position.ligne;
                while (i < p->taille-1)
                {
                    if (strcmp(p->cases[i + 1][j], ".") == 0 || strcmp(p->cases[i + 1][j], "⬛") == 0 || strcmp(p->cases[i + 1][j], "⬜") == 0)
                    {
                        if (piece.joueur == BLANC)
                            strcpy(p->cases[i + 1][j], "⬜");
                        else
                            strcpy(p->cases[i + 1][j], "⬛");
                        i++;
                    }
                    else i = p->taille;
                }
                i=position.ligne-1;
                j=position.colonne-1;
                while (j > 0)
                {
                    if (strcmp(p->cases[i][j - 1], ".") == 0 || strcmp(p->cases[i][j - 1], "⬛") == 0 || strcmp(p->cases[i][j - 1], "⬜") == 0)
                    {
                        if (piece.joueur == BLANC)
                            strcpy(p->cases[i][j - 1], "⬜");
                        else
                            strcpy(p->cases[i][j - 1], "⬛");
                        j--;
                    }
                    else j = 0;
                }
                j = position.colonne;
                while (j < p->taille-1)
                {
                    if (strcmp(p->cases[i][j + 1], ".") == 0 || strcmp(p->cases[i][j + 1], "⬛") == 0 || strcmp(p->cases[i][j + 1], "⬜") == 0)
                    {
                        if (piece.joueur == BLANC)
                            strcpy(p->cases[i][j + 1], "⬜");
                        else
                            strcpy(p->cases[i][j + 1], "⬛");
                        j++;
                    }
                    else j = p->taille;
                }

                return 1;
            };

        case CAVALIER:;
        case FOU:;
        case DAME:;
        case ROI:;
        default: return -1;
    }
}
