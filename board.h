#ifndef BOARD_H
#define BOARD_H

#define MAX_TAILLE 12

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

typedef struct {
    char symbole[5]; // Unicode = chaîne de caractères, symbole de la piece sur l'échiquier
    Joueur joueur;
    TypePiece type;
} Piece;

typedef struct {
    int taille;
    char* cases[MAX_TAILLE][MAX_TAILLE];
} Plateau;

typedef struct
{
    int ligne;
    int colonne;
}Position;

void initialiser_plateau(Plateau* p);//met des points dans toutes les cases du tableau
void afficher_plateau(Plateau p);//affiche le tableau
void definir_symbole(Piece* p);//conversion dy symbole
TypePiece conversion_type(const char* saisie);
extern const char* symboles[2][6];
Joueur conversion_joueur(int j1);

#endif
