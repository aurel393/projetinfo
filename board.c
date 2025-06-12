
#include <stdio.h>
#include "board.h"
#include <stdlib.h>
#include <string.h>


/**
 * @brief Initialise toutes les cases du plateau avec le symbole vide ". ".
 *
 * Elle doit être appelée avant le début d’une partie pour garantir
 * un état propre du plateau.
 *
 * @param p Pointeur vers la structure Plateau à initialiser.
 */

void initialiser_plateau(Plateau* p)
{
    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            p->cases[i][j] = strdup(". ");
        }
    }
}
/**
 * @brief Initialise le tableau des types de pièces capturées à -1.
 *
 * Cette fonction met à -1 chaque case du tableau `types_capture` du plateau, indiquant
 * qu’aucune pièce n’a encore été capturée à cette position. Elle doit être appelée au début
 * de partie pour être sûr que le fichier de sauvegarde reste propre et lisible.
 *
 * @param p Pointeur vers le Plateau dont le tableau de capture doit être initialisé.
 */

void initialiser_tableau_capture(Plateau *p)
{
    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            p->types_capture[i][j] = -1;
        }
    }
}

/**
 * @brief Définit le symbole Unicode correspondant à une pièce.
 *
 * En fonction du type de la pièce et du joueur (NOIR ou BLANC), cette fonction assigne
 * le bon caractère Unicode dans le champ `symbole` de la structure `Piece`.
 * Si les valeurs sont invalides, elle assigne un caractère générique '?'.
 *
 * @param p Pointeur vers la structure Piece à laquelle associer un symbole.
 */

void definir_symbole(Piece* p) {
    if (p->type >= 0 && p->type < 6 && p->joueur >= 0 && p->joueur <= NOIR) {//test de vérification
        // Copie la chaîne de symbole Unicode correspondante dans p->symbole
        strcpy(p->symbole, symboles[p->joueur][p->type]);
    } else {
        // En cas de valeur invalide, on met un symbole générique
        strcpy(p->symbole, "?");
    }
}
/**
 * @brief Tableau global contenant les symboles Unicode pour chaque type de pièce et joueur.
 *
 * Ce tableau permet d’associer directement un caractère visuel à un type de pièce selon
 * qu’elle appartient au joueur noir (index 0) ou blanc (index 1). S'utilise avec la fonction
 * definir_symbole.
 *
 * Exemple : symboles[NOIR][PION] => "♙ ", symboles[BLANC][DAME] => "♛ "
 */

const char* symboles[2][6] = {
    // JOUEUR1 (noir)
    { "♙ ", "♖ ", "♘ ", "♗ ", "♕ ", "♔ " },
    // JOUEUR2 (blanc)
    { "♟ ", "♜ ", "♞ ", "♝ ", "♛ ", "♚ " }
};


/**
 * @brief Convertit une chaîne de caractères en type de pièce (enum TypePiece).
 *
 * Cette fonction permet de traduire une saisie utilisateur (par exemple "pion")
 * en une valeur de l'énumération `TypePiece`. Si la chaîne ne correspond à aucun
 * type connu, elle retourne -1.
 *
 * @param saisie Chaîne saisie par l'utilisateur (ex : "roi", "tour", etc.).
 * @return TypePiece correspondant, ou -1 si la saisie est invalide.
 */

TypePiece conversion_type(const char* saisie) {
    if (strcmp(saisie, "pion") == 0) return PION;
    if (strcmp(saisie, "tour") == 0) return TOUR;
    if (strcmp(saisie, "cavalier") == 0) return CAVALIER;
    if (strcmp(saisie, "fou") == 0) return FOU;
    if (strcmp(saisie, "dame") == 0) return DAME;
    if (strcmp(saisie, "roi") == 0) return ROI;
    return -1; // Invalide
}

/**
 * @brief Convertit un entier représentant un joueur en enum Joueur.
 *
 * Permet d'utiliser un entier (par exemple 1 ou 2) pour déterminer le joueur correspondant
 * dans l'énumération `Joueur`. Par convention, 1 correspond au joueur NOIR, sinon BLANC.
 *
 * @param j1 Entier représentant un joueur, définit aléatoirement.
 * @return Valeur de l’énumération Joueur : NOIR ou BLANC.
 */

Joueur conversion_joueur(int j1) { // convertis un int du joueur en enum pour aller dans la structure
    if (j1 == 1) return NOIR;
    else return BLANC;
}


/**
 * @brief Affiche l’état actuel du plateau dans la console.
 *
 * Cette fonction parcourt le plateau et imprime tous les symboles ligne par ligne
 * afin de donner une représentation visuelle du jeu.
 *
 * @param p Structure Plateau à afficher.
 */

void afficher_plateau(Plateau p) {
    for (int i = 0; i < p.taille; i++) {
        for (int j = 0; j < p.taille; j++) {
            printf("%s ", p.cases[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Libère dynamiquement la mémoire allouée pour le plateau de jeu.
 *
 * Cette fonction parcourt chaque case du tableau `cases` du plateau,
 * et libère la mémoire allouée avec `strdup()` pour chaque chaîne.
 * Elle est à appeler à la fin du programme pour éviter les fuites mémoire.
 *
 * @param p Pointeur vers le plateau à nettoyer.
 */
void liberer_plateau(Plateau *p) {
    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            free(p->cases[i][j]);
        }
    }
}


