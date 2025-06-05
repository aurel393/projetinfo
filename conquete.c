//
// Created by aurel on 22/05/25.
//

#include "conquete.h"
#include <stdio.h>
#include "board.h"
#include <string.h>
#include "menu.h"
#include "compteur.h"
#include "sauvegarde.h"
void conquete(Plateau *p, int j1, CompteurPiece cpj1, CompteurPiece cpj2)
{
    Piece piece;
    TypePiece type;
    Joueur j=conversion_joueur(j1);
    Position pos1;
    char saisie[10];
    int choix=menu_jeu(j),i=0,exit=0;

    while (choix==1)
    {
        do
        {
            printf("Quelle pièce voulez vous placer ? \n");
            scanf("%9s", saisie);  // lis une chaîne de 9 caracteres + \0
            type= conversion_type(saisie);
        }while (type==-1); //demande de la saisie de la pièce avec vérification
        piece.type=type;
        piece.joueur=j;
        definir_symbole(&piece);

        //les lignes suivantes vérifient et mettent à jour les coordonnées entrées par l'utilisateur
        do {
            printf("Entrez la ligne (1 à %d) : ", p->taille);
            scanf("%d", &pos1.ligne);
        } while (pos1.ligne < 1 || pos1.ligne > p->taille);

        do {
            printf("Entrez la colonne (1 à %d) : ", p->taille);
            scanf("%d", &pos1.colonne);
        } while (pos1.colonne < 1 || pos1.colonne > p->taille);

        //vérifie si il n'y a pas déjà une pièce sur la case

        if(strcmp(p->cases[pos1.ligne-1][pos1.colonne-1],". ") == 0 || strcmp(p->cases[pos1.ligne-1][pos1.colonne-1],"◽") == 0 || strcmp(p->cases[pos1.ligne-1][pos1.colonne-1],"◾")==0)
        {
            if ((cpj1.compt[piece.type] != 0 && j==BLANC ) || (cpj2.compt[piece.type] != 0 && j==NOIR))//vérifie qu'on puisse encore poser des pièces
            {
                strcpy(p->cases[pos1.ligne-1][pos1.colonne-1], piece.symbole);//met à jour le plateau
                deplacement(p,piece,pos1);
                if (j==BLANC) compteur(&cpj1,piece.type);
                else compteur(&cpj2,piece.type);
                afficher_plateau(*p);
                while (i<=5)//vérifie si les compteurs sont à 0
                {
                    if (cpj1.compt[i]==0 && cpj2.compt[i]==0) i++;
                    else i=6;

                    if(i==5)
                    {
                        comptage(p);//tous les compteurs sont à 0 -> on compte les points
                        exit=1;
                    }
                }
                if (exit==1) break;
                i=0;
                choix=menu_jeu(j);
                //changement des couleurs
                if (j==BLANC) j=NOIR;
                else j=BLANC;
            }
            else
            {
                printf("Vous n'avez plus de %sdisponible\n", piece.symbole);
                afficher_plateau(*p);
            }
        }
        else
        {
            printf("Il y a déjà une pièce sur cette case ! \n");
            afficher_plateau(*p);
        }
    }
    if (choix==2)
    {
        if (j==1) printf("Fin de partie ! Les noirs ont gagnés");
        else printf("Fin de partie ! Les blancs ont gagnés");
    }
    if (choix==3)
    {
        sauvegarde(p,j,2,cpj1,cpj2);
    }
}


void comptage(Plateau *p)
{
    int blanc=0,noir=0;
    for (int i=0; i<p->taille; i++)
    {
        for (int j=0; j<p->taille; j++)
        {
            if (strcmp(p->cases[i][j],"◽")==0) blanc++;
            if (strcmp(p->cases[i][j],"◾")==0) noir++;
        }
    }
    if (blanc>noir) printf("Bravo, les blancs ont gagnés avec %d points contre %d !!",blanc, noir);
    else if (noir>blanc) printf("Bravo, les noirs ont gagnés avec %d points contre %d !!",noir,blanc);
    else printf("égalité, les deux joueurs ont marqués %d points !!",blanc);

}


void deplacement(Plateau *p, Piece piece, Position position)
{
    int i = position.ligne -1;
    int j = position.colonne-1;
    int k,l;
    switch (piece.type)
    {
    case PION:
        {
            if (piece.joueur == NOIR)
            {
                if (i-1>0)
                {
                    if (strcmp(p->cases[i-1][j],". ") == 0 || strcmp(p->cases[i-1][j],"◽") == 0 || strcmp(p->cases[i-1][j],"◾")==0)
                    {
                        strcpy(p->cases[i-1][j],"◽");
                    }
                    else break;
                }
            }
            else
            {
                if (i+1<p->taille-1)
                {
                    if (strcmp(p->cases[i + 1][j], ". ") == 0 || strcmp(p->cases[i + 1][j], "◽") == 0 || strcmp(p->cases[i + 1][j], "◾") == 0)
                    {
                        strcpy(p->cases[i + 1][j], "◾");
                    }
                    else break;
                }
            }
            break;
        };

    case TOUR:
        {
            k=i;
            while (k>0)
            {
                if (strcmp(p->cases[k-1][j],". ") == 0 || strcmp(p->cases[k-1][j],"◽") == 0 || strcmp(p->cases[k-1][j],"◾")==0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][j],"◾");
                    else strcpy(p->cases[k-1][j] ,"◽");
                    k--;
                }
                else break;
            }
            k=i;
            while (k < p->taille-1)
            {
                if (strcmp(p->cases[k + 1][j], ". ") == 0 || strcmp(p->cases[k + 1][j], "◽") == 0 || strcmp(p->cases[k + 1][j], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k + 1][j], "◾");
                    else strcpy(p->cases[k + 1][j], "◽");
                    k++;
                }
                else break;
            }

            k=j;
            while (k > 0)
            {
                if (strcmp(p->cases[i][k - 1], ". ") == 0 || strcmp(p->cases[i][k - 1], "◽") == 0 || strcmp(p->cases[i][k - 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC)
                        strcpy(p->cases[i][k - 1], "◾");
                    else
                        strcpy(p->cases[i][k - 1], "◽");
                    k--;
                }
                else break;
            }
            k=j;
            while (k < p->taille-1)
            {
                if (strcmp(p->cases[i][k + 1], ". ") == 0 || strcmp(p->cases[i][k + 1], "◽") == 0 || strcmp(p->cases[i][k + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC)
                        strcpy(p->cases[i][k + 1], "◾");
                    else
                        strcpy(p->cases[i][k + 1], "◽");
                    k++;
                }
                else break;
            }
        break;
        };

    case CAVALIER:
        {
            if (i + 1 < p->taille && j + 2 < p->taille)
            {
                if (strcmp(p->cases[i+1][j+2],". ")==0 || strcmp(p->cases[i+1][j+2],"◽") == 0 || strcmp(p->cases[i+1][j+2],"◾")==0 )
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+1][j+2],"◾");
                    else strcpy(p->cases[i+1][j+2] ,"◽");
                }
            }
            if (i - 2 >= 0 && j - 1 >= 0) {
                if (strcmp(p->cases[i-2][j-1], ". ") == 0 || strcmp(p->cases[i-2][j-1], "◽") == 0 || strcmp(p->cases[i-2][j-1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i-2][j-1], "◾");
                    else strcpy(p->cases[i-2][j-1], "◽");
                }
            }

            // (i - 2, j + 1)
            if (i - 2 >= 0 && j + 1 < p->taille) {
                if (strcmp(p->cases[i-2][j+1], ". ") == 0 || strcmp(p->cases[i-2][j+1], "◽") == 0 || strcmp(p->cases[i-2][j+1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i-2][j+1], "◾");
                    else strcpy(p->cases[i-2][j+1], "◽");
                }
            }

            // (i - 1, j - 2)
            if (i - 1 >= 0 && j - 2 >= 0) {
                if (strcmp(p->cases[i-1][j-2], ". ") == 0 || strcmp(p->cases[i-1][j-2], "◽") == 0 || strcmp(p->cases[i-1][j-2], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i-1][j-2], "◾");
                    else strcpy(p->cases[i-1][j-2], "◽");
                }
            }

            // (i - 1, j + 2)
            if (i - 1 >= 0 && j + 2 < p->taille) {
                if (strcmp(p->cases[i-1][j+2], ". ") == 0 || strcmp(p->cases[i-1][j+2], "◽") == 0 || strcmp(p->cases[i-1][j+2], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i-1][j+2], "◾");
                    else strcpy(p->cases[i-1][j+2], "◽");
                }
            }

            // (i + 1, j - 2)
            if (i + 1 < p->taille && j - 2 >= 0) {
                if (strcmp(p->cases[i+1][j-2], ". ") == 0 || strcmp(p->cases[i+1][j-2], "◽") == 0 || strcmp(p->cases[i+1][j-2], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+1][j-2], "◾");
                    else strcpy(p->cases[i+1][j-2], "◽");
                }
            }

            // (i + 1, j + 2)
            if (i + 1 < p->taille && j + 2 < p->taille) {
                if (strcmp(p->cases[i+1][j+2], ". ") == 0 || strcmp(p->cases[i+1][j+2], "◽") == 0 || strcmp(p->cases[i+1][j+2], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+1][j+2], "◾");
                    else strcpy(p->cases[i+1][j+2], "◽");
                }
            }

            // (i + 2, j - 1)
            if (i + 2 < p->taille && j - 1 >= 0) {
                if (strcmp(p->cases[i+2][j-1], ". ") == 0 || strcmp(p->cases[i+2][j-1], "◽") == 0 || strcmp(p->cases[i+2][j-1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+2][j-1], "◾");
                    else strcpy(p->cases[i+2][j-1], "◽");
                }
            }

            // (i + 2, j + 1)
            if (i + 2 < p->taille && j + 1 < p->taille) {
                if (strcmp(p->cases[i+2][j+1], ". ") == 0 || strcmp(p->cases[i+2][j+1], "◽") == 0 || strcmp(p->cases[i+2][j+1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+2][j+1], "◾");
                    else strcpy(p->cases[i+2][j+1], "◽");
                }
            }
            break;
        };
    case FOU:
        {
            k=i;
            l=j;
            while (k>0 && l>0)
            {
                if (strcmp(p->cases[k-1][l-1],". ") == 0 || strcmp(p->cases[k-1][l-1],"◽") == 0 || strcmp(p->cases[k-1][l-1],"◾")==0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][l-1],"◾");
                    else strcpy(p->cases[k-1][l-1] ,"◽");
                    k--;
                    l--;
                }
                else break;
            }
            k=i;
            l=j;
            while (k < p->taille-1 && l > 0)
            {
                if (strcmp(p->cases[k + 1][l-1], ". ") == 0 || strcmp(p->cases[k + 1][l-1], "◽") == 0 || strcmp(p->cases[k + 1][l-1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k + 1][l-1], "◾");
                    else strcpy(p->cases[k + 1][l-1], "◽");
                    k++;
                    l--;
                }
                else break;
            }

            k=i;
            l=j;
            while (k > 0 && l < p->taille-1)
            {
                if (strcmp(p->cases[k-1][l + 1], ". ") == 0 || strcmp(p->cases[k-1][l + 1], "◽") == 0 || strcmp(p->cases[k-1][l + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][l + 1], "◾");
                    else strcpy(p->cases[k-1][l + 1], "◽");
                    k--;
                    l++;
                }
                else break;
            }
            k=i;
            l=j;
            while (k < p->taille-1 && l< p->taille-1)
            {
                if (strcmp(p->cases[k+1][l + 1], ". ") == 0 || strcmp(p->cases[k+1][l + 1], "◽") == 0 || strcmp(p->cases[k+1][l + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k+1][l + 1], "◾");
                    else strcpy(p->cases[k+1][l + 1], "◽");
                    k++;
                    l++;
                }
                else break;
            }
            break;
        };
    case DAME:
        {
            k=i;
            while (k>0)
            {
                if (strcmp(p->cases[k-1][j],". ") == 0 || strcmp(p->cases[k-1][j],"◽") == 0 || strcmp(p->cases[k-1][j],"◾")==0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][j],"◾");
                    else strcpy(p->cases[k-1][j] ,"◽");
                    k--;
                }
                else break;
            }
            k=i;
            while (k < p->taille-1)
            {
                if (strcmp(p->cases[k + 1][j], ". ") == 0 || strcmp(p->cases[k + 1][j], "◽") == 0 || strcmp(p->cases[k + 1][j], "◾") == 0)
                {
                    if (piece.joueur == BLANC)
                        strcpy(p->cases[k + 1][j], "◾");
                    else
                        strcpy(p->cases[k + 1][j], "◽");
                    k++;
                }
                else break;
            }

            k=j;
            while (k > 0)
            {
                if (strcmp(p->cases[i][k - 1], ". ") == 0 || strcmp(p->cases[i][k - 1], "◽") == 0 || strcmp(p->cases[i][k - 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC)
                        strcpy(p->cases[i][k - 1], "◾");
                    else
                        strcpy(p->cases[i][k - 1], "◽");
                    k--;
                }
                else break;
            }
            k=j;
            while (k < p->taille-1)
            {
                if (strcmp(p->cases[i][k + 1], ". ") == 0 || strcmp(p->cases[i][k + 1], "◽") == 0 || strcmp(p->cases[i][k + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC)
                        strcpy(p->cases[i][k + 1], "◾");
                    else
                        strcpy(p->cases[i][k + 1], "◽");
                    k++;
                }
                else break;
            }
            k=i;
            l=j;
            while (k>0 && l>0)
            {
                if (strcmp(p->cases[k-1][l-1],". ") == 0 || strcmp(p->cases[k-1][l-1],"◽") == 0 || strcmp(p->cases[k-1][l-1],"◾")==0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][l-1],"◾");
                    else strcpy(p->cases[k-1][l-1] ,"◽");
                    k--;
                    l--;
                }
                else break;
            }
            k=i;
            l=j;
            while (k < p->taille-1 && l > 0)
            {
                if (strcmp(p->cases[k + 1][l-1], ". ") == 0 || strcmp(p->cases[k + 1][l-1], "◽") == 0 || strcmp(p->cases[k + 1][l-1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k + 1][l-1], "◾");
                    else strcpy(p->cases[k + 1][l-1], "◽");
                    k++;
                    l--;
                }
                else break;
            }

            k=i;
            l=j;
            while (k > 0 && l < p->taille-1)
            {
                if (strcmp(p->cases[k-1][l + 1], ". ") == 0 || strcmp(p->cases[k-1][l + 1], "◽") == 0 || strcmp(p->cases[k-1][l + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][l + 1], "◾");
                    else strcpy(p->cases[k-1][l + 1], "◽");
                    k--;
                    l++;
                }
                else break;
            }
            k=i;
            l=j;
            while (k < p->taille-1 && l< p->taille-1)
            {
                if (strcmp(p->cases[k+1][l + 1], ". ") == 0 || strcmp(p->cases[k+1][l + 1], "◽") == 0 || strcmp(p->cases[k+1][l + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k+1][l + 1], "◾");
                    else strcpy(p->cases[k+1][l + 1], "◽");
                    k++;
                    l++;
                }
                else break;
            }
                break;
            };
            case ROI:
                {
                    k=i;
                    if (strcmp(p->cases[k-1][j],". ") == 0 || strcmp(p->cases[k-1][j],"◽") == 0 || strcmp(p->cases[k-1][j],"◾")==0)
                    {
                        if (piece.joueur == BLANC) strcpy(p->cases[k-1][j],"◾");
                        else strcpy(p->cases[k-1][j] ,"◽");
                    }
                    k=i;
                    if (strcmp(p->cases[k + 1][j], ". ") == 0 || strcmp(p->cases[k + 1][j], "◽") == 0 || strcmp(p->cases[k + 1][j], "◾") == 0)
                    {
                        if (piece.joueur == BLANC)
                            strcpy(p->cases[k + 1][j], "◾");
                        else
                            strcpy(p->cases[k + 1][j], "◽");
                    }
                    k=j;
                    if (strcmp(p->cases[i][k - 1], ". ") == 0 || strcmp(p->cases[i][k - 1], "◽") == 0 || strcmp(p->cases[i][k - 1], "◾") == 0)
                    {
                        if (piece.joueur == BLANC)
                            strcpy(p->cases[i][k - 1], "◾");
                        else
                            strcpy(p->cases[i][k - 1], "◽");
                    }
                    k=j;
                    if (strcmp(p->cases[i][k + 1], ". ") == 0 || strcmp(p->cases[i][k + 1], "◽") == 0 || strcmp(p->cases[i][k + 1], "◾") == 0)
                    {
                        if (piece.joueur == BLANC)
                            strcpy(p->cases[i][k + 1], "◾");
                        else
                            strcpy(p->cases[i][k + 1], "◽");
                    }

                    k=i;
                    l=j;
                    if (strcmp(p->cases[k-1][l-1],". ") == 0 || strcmp(p->cases[k-1][l-1],"◽") == 0 || strcmp(p->cases[k-1][l-1],"◾")==0)
                    {
                        if (piece.joueur == BLANC) strcpy(p->cases[k-1][l-1],"◾");
                        else strcpy(p->cases[k-1][l-1] ,"◽");
                    }
                    k=i;
                    l=j;
                    if (strcmp(p->cases[k + 1][l-1], ". ") == 0 || strcmp(p->cases[k + 1][l-1], "◽") == 0 || strcmp(p->cases[k + 1][l-1], "◾") == 0)
                    {
                        if (piece.joueur == BLANC) strcpy(p->cases[k + 1][l-1], "◾");
                        else strcpy(p->cases[k + 1][l-1], "◽");
                    }

                    k=i;
                    l=j;
                    if (strcmp(p->cases[k-1][l + 1], ". ") == 0 || strcmp(p->cases[k-1][l + 1], "◽") == 0 || strcmp(p->cases[k-1][l + 1], "◾") == 0)
                    {
                        if (piece.joueur == BLANC) strcpy(p->cases[k-1][l + 1], "◾");
                        else strcpy(p->cases[k-1][l + 1], "◽");
                    }
                    k=i;
                    l=j;
                    if (strcmp(p->cases[k+1][l + 1], ". ") == 0 || strcmp(p->cases[k+1][l + 1], "◽") == 0 || strcmp(p->cases[k+1][l + 1], "◾") == 0)
                    {
                        if (piece.joueur == BLANC) strcpy(p->cases[k+1][l + 1], "◾");
                        else strcpy(p->cases[k+1][l + 1], "◽");
                    }
                    break;
                };
            default: break;
        }
    }