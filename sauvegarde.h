
#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "board.h"
#include "compteur.h"

int sauvegarde(Plateau *p, int joueurencours, int mode, CompteurPiece cpj1, CompteurPiece cpj2);
int chargement(Plateau *p, int *joueur, int *mode, CompteurPiece *cpj1, CompteurPiece *cpj2);
#endif //SAUVEGARDE_H