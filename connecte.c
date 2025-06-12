

#include "connecte.h"
#include "board.h"
#include "compteur.h"
#include "menu.h"
#include "conquete.h"
#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"

void connecte(Plateau *p, int j1,CompteurPiece cpj1, CompteurPiece cpj2 )
{
    Piece piece;
    TypePiece type;
    Joueur j=conversion_joueur(j1);
    Position pos1;
    char saisie[10];
    int exit=0, choix=menu_jeu(j),verif=-1;

    while (choix==1)
    {

        while (verif==-1)
        {
            do
            {
                printf("Quelle pièce voulez vous placer (ex: pion, tour...)? \n");
                scanf("%9s", saisie);  // lis une chaîne de 9 caracteres + \0
                type= conversion_type(saisie);
            }while (type==-1); //demande de la saisie de la pièce avec vérification
            piece.type=type;
            piece.joueur=j;
            definir_symbole(&piece);//inscrit l'emoji correspondant à la pièce suivant le nom entré par l'utilisateur

            //les lignes suivantes vérifient et mettent à jour les coordonnées entrées par l'utilisateur
            do {
                printf("Entrez la ligne (1 à %d) : ", p->taille);
                scanf("%d", &pos1.ligne);
            } while (pos1.ligne < 1 || pos1.ligne > p->taille);

            do {
                printf("Entrez la colonne (1 à %d) : ", p->taille);
                scanf("%d", &pos1.colonne);
            } while (pos1.colonne < 1 || pos1.colonne > p->taille);
            verif=verification(p,piece,j,pos1,cpj1,cpj2);
        }

        strcpy(p->cases[pos1.ligne-1][pos1.colonne-1], piece.symbole);//met à jour le plateau
        deplacement(p,piece,pos1);//fonction qui gère les cases sur lesquelles les pièces peuvent se déplacer
        if (j==BLANC) compteur(&cpj1,piece.type);//met à jour le compteur en fonction du joueur
        else compteur(&cpj2,piece.type);
        afficher_plateau(*p);

        if (cpj1.compt[ROI]==0 || cpj2.compt[ROI]==0)//si un des joueurs pose son roi, on compte les points
        {
            comptage(p,2,cpj1,cpj2);
            exit=1;
        }

        if (exit==1) break;
        if (j==BLANC) j=NOIR;
        else j=BLANC;
        choix=menu_jeu(j);
        verif=-1;
    }
    if (choix==2)
    {
        if (j==1) printf("Fin de partie ! Les noirs ont gagnés\n");
        else printf("Fin de partie ! Les blancs ont gagnés\n");
    }
    if (choix==3)
    {
        if (sauvegarde(p, j,2,cpj1,cpj2) == -1) {
            printf("Erreur lors de la sauvegarde de la partie.\n");
        }
        else printf("Partie sauvegardée avec succès. \n");
    }
}


/**
 * Fonction qui vérifie si une pièce peut être placée sur le plateau dans le mode Connecte.
 *
 * @param p     Pointeur vers le plateau de jeu
 * @param piece La pièce à placer
 * @param j     Le joueur (BLANC ou NOIR)
 * @param pos1  La position où la pièce doit être placée
 * @param cpj1  Compteur de pièces du joueur 1
 * @param cpj2  Compteur de pièces du joueur 2
 *
 * @return 1 si la pièce peut être placée, -1 sinon
 */

int verification(Plateau *p,Piece piece, Joueur j, Position pos1,CompteurPiece cpj1,CompteurPiece cpj2)
{
    int x=pos1.ligne-1;
    int y=pos1.colonne-1;
    if ((cpj1.compt[piece.type] != 0 && j==BLANC ) || (cpj2.compt[piece.type] != 0 && j==NOIR))
    {
        if(strcmp(p->cases[x][y],". ") == 0 || strcmp(p->cases[x][y],"◽") == 0 || strcmp(p->cases[x][y],"◾")==0)
        {
            switch (piece.type)
            {
            case PION:
                {
                    return 1;
                }
            case CAVALIER:
                {
                    if (p->types_capture[x][y] == PION) return 1;
                    printf("Les cavaliers peuvent seulement être posés sur des cases capturées par des pions\n");
                    return -1;
                }
            case FOU:
                {
                    if (p->types_capture[x][y] == CAVALIER) return 1;
                    printf("Les fous peuvent seulement être posés sur des cases capturées par des cavaliers\n");
                    return -1;
                }
            case TOUR:
                {
                    if (p->types_capture[x][y] == FOU) return 1;
                    printf("Les tours peuvent seulement être posés sur des cases capturées par des fous\n");
                    return -1;
                }
            case DAME:
                {
                    if (p->types_capture[x][y] == TOUR) return 1;
                    printf("La dame peut seulement être posé sur des cases capturées par des tours\n");
                    return -1;
                }
            case ROI:
                {
                    if (p->types_capture[x][y] == DAME) return 1;
                    printf("Le roi peut seulement être posé sur des cases capturées par les dames\n");
                    return -1;
                }
            }
        }
        printf("Cette case est déjà occupée\n");
        return -1;
    }
    printf("Vous n'avez plus de %s\n",piece.symbole);
    return -1;
}