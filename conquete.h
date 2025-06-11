//
// Created by aurel on 22/05/25.
//

#ifndef CONQUETE_H
#define CONQUETE_H
#include "board.h"
#include "compteur.h"

void deplacement(Plateau *p, Piece piece, Position position);
void conquete(Plateau *p, int j1, CompteurPiece cpj1, CompteurPiece cpj2);
void comptage(Plateau *p, int mode, CompteurPiece cpj1, CompteurPiece cpj2);

#endif //CONQUETE_H
