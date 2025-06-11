#ifndef BOARD_H
#define BOARD_H

#define MAX_TAILLE 12

/**
 * @brief Énumération des types de pièces disponibles dans le jeu.
 *
 * Chaque valeur correspond à un type de pièce d’échecs.
 * Permet une meilleure lisibilité du programme.
 */
typedef enum {
    PION,
    TOUR,
    CAVALIER,
    FOU,
    DAME,
    ROI
} TypePiece;

typedef enum {
    BLANC,
    NOIR
} Joueur;

/**
 * @brief Structure représentant une pièce sur le plateau.
 *
 * Contient le type de la pièce, le joueur auquel elle appartient et son symbole Unicode.
 */
typedef struct {
    char symbole[5]; // Unicode = chaîne de caractères, symbole de la piece sur l'échiquier
    Joueur joueur;
    TypePiece type;
} Piece;


/**
 * @brief Structure représentant le plateau de jeu.
 *
 * Contient la taille du plateau, les cases (chaînes de caractères représentant les pièces ou cases vides),
 * et un tableau pour les types des pièces capturées.
 */
typedef struct {
    int taille;
    char* cases[MAX_TAILLE][MAX_TAILLE];
    int types_capture[MAX_TAILLE][MAX_TAILLE];
} Plateau;

/**
 * @brief Structure représentant une position sur le plateau.
 *
 * Sert à regrouper les coordonnées d'une case par ses lignes et colonnes au même endroit.
 */
typedef struct
{
    int ligne;
    int colonne;
}Position;

void initialiser_plateau(Plateau* p);//met des points dans toutes les cases du tableau
void afficher_plateau(Plateau p);//affiche le tableau
void definir_symbole(Piece* p);//conversion dy symbole
void initialiser_tableau_capture(Plateau *p);
void liberer_plateau(Plateau *p);
TypePiece conversion_type(const char* saisie);
extern const char* symboles[2][6];
Joueur conversion_joueur(int j1);

#endif
