
#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compteur.h"
#include "board.h"

/**
 * @brief Charge une partie sauvegardée depuis un fichier texte.
 *
 * Cette fonction lit le contenu du fichier "save.txt" afin de restaurer l’état d'une partie :
 * - le joueur en cours,
 * - la taille du plateau,
 * - le mode de jeu (classique ou connecté),
 * - l’état du plateau (cases et types de capture),
 * - les compteurs de pièces pour les deux joueurs.
 *
 * Elle effectue des vérifications à chaque étape pour s'assurer que le fichier est correctement formaté.
 *
 * @param p        Pointeur vers le plateau de jeu à initialiser
 * @param joueur   Pointeur vers la variable représentant le joueur courant
 * @param mode     Pointeur vers la variable représentant le mode de jeu
 * @param cpj1     Pointeur vers les compteurs de pièces du joueur 1 (blanc)
 * @param cpj2     Pointeur vers les compteurs de pièces du joueur 2 (noir)
 *
 * @return         0 si le chargement est un succès, -1 sinon
 */

int chargement(Plateau *p, int *joueur, int *mode, CompteurPiece *cpj1, CompteurPiece *cpj2) {
    FILE *fichier = fopen("save.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }

    // Lecture du joueur courant
    if (fscanf(fichier, "Joueur: %d\n", joueur) != 1) {//regarde que le fichier est au bon format
        printf("Erreur lors de la lecture du joueur.\n");
        fclose(fichier);
        return -1;
    }

    // Lecture de la taille du plateau
    if (fscanf(fichier, "Taille: %d\n", &(p->taille)) != 1) {
        printf("Erreur lors de la lecture de la taille du plateau.\n");
        fclose(fichier);
        return -1;
    }

    // Lecture du mode de jeu
    if (fscanf(fichier, "Mode: %d\n", mode) != 1)
    {
        printf("Erreur lors de la lecture du mode.\n");
        fclose(fichier);
        return -1;
    }
    
    // Lecture du plateau
    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            static char temp[10]; // buffer temporaire pour les symboles
            char temp_modif[12];
            if (fscanf(fichier, "%9s", temp) != 1) {
                printf("Erreur lors de la lecture du plateau.\n");
                fclose(fichier);
                return -1;
            }
            if (strcmp(temp, "◽") == 0 || strcmp(temp, "◾") == 0)  p->cases[i][j] = strdup(temp);
            else
            {
                strcpy(temp_modif, temp);      // copie temp dans temp_modif
                strcat(temp_modif, " ");       // ajoute un espace à la fin pour les "." et les pièces
                p->cases[i][j] = strdup(temp_modif);
            }
        }
    }

    //Lecture du plateau des types de captures
    for (int i = 0; i < p->taille; i++)
    {
        for (int j = 0; j < p->taille; j++)
        {
            if (fscanf(fichier, "%d", &p->types_capture[i][j]) != 1) {
                printf("Erreur lors de la lecture des types de capture.\n");
                fclose(fichier);
                return -1;
            }

        }
    }


    // Lecture des compteurs du joueur 1
    for (int i = 0; i < 6; i++) {
        if (fscanf(fichier, "%d", &cpj1->compt[i]) != 1) {
            printf("Erreur lors de la lecture des compteurs du joueur 1.\n");
            fclose(fichier);
            return -1;
        }
    }

    // Lecture des compteurs du joueur 2
    for (int i = 0; i < 6; i++) {
        if (fscanf(fichier, "%d", &cpj2->compt[i]) != 1) {
            printf("Erreur lors de la lecture des compteurs du joueur 2.\n");
            fclose(fichier);
            return -1;
        }
    }

    fclose(fichier);
    if (*mode==1) printf("Mode: Conquête\n");
    else if (*mode==2) printf("Mode: Connecte\n");
    return 0;
}

/**
 * @brief Sauvegarde l’état actuel d’une partie dans un fichier texte.
 *
 * Cette fonction écrit dans le fichier "save.txt" les informations nécessaires à la reprise d’une partie :
 * - le joueur courant,
 * - la taille du plateau,
 * - le mode de jeu,
 * - l’état des cases du plateau (symboles),
 * - les types de captures pour chaque case,
 * - les compteurs de pièces pour les deux joueurs.
 *
 * Le format d’écriture doit correspondre exactement à celui attendu par la fonction `chargement`.
 *
 * @param p              Pointeur vers le plateau de jeu à sauvegarder
 * @param joueurencours Numéro du joueur dont c’est le tour (1 ou 2)
 * @param mode           Mode de jeu en cours (classique = 1, connecté = 2, etc.)
 * @param cpj1           Structure contenant les compteurs de pièces du joueur 1 (blanc)
 * @param cpj2           Structure contenant les compteurs de pièces du joueur 2 (noir)
 *
 * @return               0 si la sauvegarde a réussi, -1 en cas d’erreur d’ouverture ou d’écriture
 */

int sauvegarde(Plateau *p, int joueurencours, int mode, CompteurPiece cpj1, CompteurPiece cpj2)
{
    FILE *fichier = fopen("save.txt", "w");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier \n");
        return -1;
    }

    // Sauvegarde du joueur courant
    fprintf(fichier, "Joueur: %d\n", joueurencours);

    // Sauvegarde de la taille du plateau
    fprintf(fichier, "Taille: %d\n", p->taille);

    // Sauvegarde du mode de jeu
    fprintf(fichier, "Mode: %d\n", mode);
    
    // Sauvegarde du plateau

    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            fprintf(fichier, "%s ", p->cases[i][j]);
        }
        fprintf(fichier, "\n");
    }

    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            fprintf(fichier, "%d ", p->types_capture[i][j]);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarde des compteurs
    for (int i = 0; i < 6; i++) {
        fprintf(fichier, "%d \n", cpj1.compt[i]);
    }

    for (int i = 0; i < 6; i++) {
        fprintf(fichier, "%d \n", cpj2.compt[i]);
    }

    fclose(fichier);
    return 0;
}
