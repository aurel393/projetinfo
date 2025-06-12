
#ifndef COMPTEUR_H
#define COMPTEUR_H

/**
 * @brief Structure contenant un tableau pour compter les pièces en fonction du PieceType.
 */
typedef struct
{
    int compt[6];
}CompteurPiece;

void initialiser_compteur(CompteurPiece *cp);
int compteur(CompteurPiece *cp, TypePiece p);

#endif //COMPTEUR_H
