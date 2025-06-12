#ifndef CONNECTE_H
#define CONNECTE_H
#include"board.h"
#include"compteur.h"

void connecte(Plateau *p, int j1,CompteurPiece cpj1, CompteurPiece cpj2 );
int verification(Plateau *p,Piece piece, Joueur j, Position pos1,CompteurPiece cpj1,CompteurPiece cpj2);

#endif //CONNECTE_H
