#include "board.h"
#include "compteur.h"

/**
 * @brief Initialise un compteur de pièces avec les quantités de départ.
 *
 * Cette fonction initialise les compteurs de pièces d’un joueur avec la
 * configuration standard d’un jeu d’échecs :
 * - 8 pions,
 * - 2 tours,
 * - 2 cavaliers,
 * - 2 fous,
 * - 1 dame,
 * - 1 roi.
 *
 * Elle est appelée en début de partie pour chaque joueur.
 *
 * @param cp   Pointeur vers la structure CompteurPiece à initialiser.
 * @return Rien, modifie directement le compteur.
 */

void initialiser_compteur(CompteurPiece *cp)//met le compteur avec les bonnes pièces pour chaque joueur
{
    cp->compt[PION] = 8;
    cp->compt[TOUR] = 2;
    cp->compt[CAVALIER] = 2;
    cp->compt[FOU] = 2;
    cp->compt[DAME] = 1;
    cp->compt[ROI] = 1;
}

/**
 * @brief Décrémente le compteur d'une pièce si elle est disponible.
 *
 * Cette fonction vérifie si une pièce du type spécifié est encore disponible
 * (c’est-à-dire si le compteur correspondant est supérieur à 0). Si oui, elle
 * décrémente ce compteur et retourne 0. Sinon, elle retourne -1 pour signaler
 * que la pièce n’est plus disponible.
 *
 * Cette logique permet de s’assurer qu’un joueur ne peut pas poser plus de
 * pièces qu’il ne devrait.
 *
 * @param cp   Pointeur vers le compteur de pièces du joueur.
 * @param p    Type de pièce à utiliser (PION, TOUR, CAVALIER, etc.).
 *
 * @return     0 si la pièce a été utilisée avec succès, -1 si le quota est dépassé.
 */

int compteur(CompteurPiece *cp, TypePiece p)
{
    if (cp->compt[p] > 0)
    {
        cp->compt[p] --;
        return 0;
    }
    return -1;
}
