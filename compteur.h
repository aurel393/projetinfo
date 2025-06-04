//
// Created by aurel on 22/05/25.
//

#ifndef COMPTEUR_H
#define COMPTEUR_H

typedef struct
{
    int compt[6];
}CompteurPiece;

void initialiser_compteur(CompteurPiece *cp);
int compteur(CompteurPiece *cp, TypePiece p);

#endif //COMPTEUR_H
