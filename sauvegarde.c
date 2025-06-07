//
// Created by aurel on 23/05/25.
//

#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compteur.h"
#include "board.h"


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
    
    // Lecture du plateau A MODIFIER NE RECHARGE PAS LES ESPACES APRES LES POINTS
    for (int i = 0; i < p->taille; i++) {
        for (int j = 0; j < p->taille; j++) {
            static char temp[10]; // buffer temporaire pour les symboles
            if (fscanf(fichier, "%9s", temp) != 1) {
                printf("Erreur lors de la lecture du plateau.\n");
                fclose(fichier);
                return -1;
            }
            // Alloue et copie le symbole
            if (strcmp(temp, ".")==0) strcpy(temp, ". ");
            p->cases[i][j] = strdup(temp);
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
    return 0;
}


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