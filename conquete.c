
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
            printf("Quelle pièce voulez vous placer (ex: pion, tour...)? \n");
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
                deplacement(p,piece,pos1);//fonction qui gère les cases sur lesquelles les pièces peuvent se déplacer
                if (j==BLANC) compteur(&cpj1,piece.type);//met à jour le compteur en fonction du joueur
                else compteur(&cpj2,piece.type);
                afficher_plateau(*p);
                while (i<=5)//vérifie si les compteurs sont à 0
                {
                    if (cpj1.compt[i]==0 && cpj2.compt[i]==0) i++;
                    else i=6;

                    if(i==5)
                    {
                        comptage(p,0,cpj1,cpj2);//tous les compteurs sont à 0 -> on compte les points
                        exit=1;
                    }
                }
                if (exit==1) break;
                i=0;
                if (j==BLANC) j=NOIR;
                else j=BLANC;
                choix=menu_jeu(j);
                //changement des couleurs

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
        if (j==1) printf("Fin de partie ! Les noirs ont gagnés\n");
        else printf("Fin de partie ! Les blancs ont gagnés\n");
    }
    if (choix==3)
    {
        if (sauvegarde(p, j,1,cpj1,cpj2) == -1) {
            printf("Erreur lors du chargement de la partie.\n");
        }
    }
}

/**
 * @brief Calcule et affiche le score final des deux joueurs en fonction des cases capturées
 *        et des pièces placées sur le plateau.
 *
 * Cette fonction compte le nombre de cases capturées sur l'ensemble du plateau.
 * Ensuite, elle ajoute 16 points à chaque joueur pour représenter les pièces
 * théoriquement disponibles au départ. En mode connecté (mode == 2), on soustrait le nombre de pièces
 * restantes dans les compteurs pour tenir compte uniquement des pièces effectivement posées.
 *
 * @param p     Pointeur vers le plateau de jeu
 * @param mode  Mode de jeu (si mode == 2, on utilise les compteurs pour affiner le score)
 * @param cpj1  Compteur des pièces restantes pour le joueur 1 (BLANC)
 * @param cpj2  Compteur des pièces restantes pour le joueur 2 (NOIR)
 *
 * @return      Aucun (la fonction affiche le résultat directement dans la console)
 */
void comptage(Plateau *p,int mode, CompteurPiece cpj1, CompteurPiece cpj2)
{
    int blanc=0,noir=0;
    for (int i=0; i<p->taille; i++)
    {
        for (int j=0; j<p->taille; j++)
        {
            if (strcmp(p->cases[i][j],"◽")==0) blanc++;//on compte les cases capturées par les blancs puis par les noirs
            if (strcmp(p->cases[i][j],"◾")==0) noir++;
        }
    }

    blanc=blanc+16;//on ajoute 16 peu importe le mode pour compter les pièces posés
    noir=noir+16;

    if (mode==2)//en mode connecte, comme toutes les pièces ne sont pas sûres d'être posées, on retire la valeur de chaque compteur
    {
        for (int i=0;i<6;i++)
        {
            blanc=blanc-cpj1.compt[i];
            noir=noir-cpj2.compt[i];
        }
    }
    if (blanc>noir) printf("Bravo, les blancs ont gagnés avec %d points contre %d !!\n",blanc, noir);
    else if (noir>blanc) printf("Bravo, les noirs ont gagnés avec %d points contre %d !!\n",noir,blanc);
    else printf("égalité, les deux joueurs ont marqués %d points !!\n",blanc);

}

/**
 * @brief Met à jour le plateau en marquant les cases capturées par la pièce posée,
 *        selon les règles spécifiques au type de pièce.
 *
 * Cette fonction analyse la position d'une pièce fraîchement posée et marque les cases
 * autour (ou dans des directions particulières) comme capturées, en fonction du type de pièce.
 * Ces cases sont ensuite identifiées visuellement
 * sur le plateau par un symbole spécifique (◽ pour le joueur NOIR, ◾ pour le joueur BLANC),
 * et leur type de capture est enregistré dans le tableau `types_capture`.
 *
 * Elle inclut aussi des vérifications de bornes pour éviter les débordements sur le plateau.
 *
 * @param p         Pointeur vers le plateau de jeu à modifier
 * @param piece     La pièce jouée (inclut son type et son joueur)
 * @param position  Position sur le plateau où la pièce a été placée
 *
 * @return          Aucun (les modifications sont faites directement sur le plateau)
 */
void deplacement(Plateau *p, Piece piece, Position position)
{
    int i = position.ligne -1;
    int j = position.colonne-1;
    int k,l;
    switch (piece.type)
    {
    case PION:
        {
            if (piece.joueur == NOIR)//La seule difficulté pour cette pièece est la gestion des deux directions pour le pion en fonction de la couleur
            {
                if (i>0)
                {//la ligne de code suivante est présente de nombreuse fois: elle vérifie si la case est vide, blanche ou noir.
                    //Dans ce cas, la fonction capture la case en fonction de la couleur, dans l'autre elle ne fait rien.
                    //Nous aurions pu faire une fonction pour vérifier cette condition et l'utiliser dans tout le code mais nous y avons pensé à la fin.
                    if (strcmp(p->cases[i-1][j],". ") == 0 || strcmp(p->cases[i-1][j],"◽") == 0 || strcmp(p->cases[i-1][j],"◾")==0)
                    {
                        strcpy(p->cases[i-1][j],"◽");
                        p->types_capture[i-1][j]=PION;
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
                        p->types_capture[i+1][j]=PION;
                    }
                    else break;
                }
            }
            break;
        };

    case TOUR://regarde les 4 positions sans dépasser les bornes du tableau et remplace les cases en fonction de la couleur.
        {
            k=i;
            while (k>0)
            {
                if (strcmp(p->cases[k-1][j],". ") == 0 || strcmp(p->cases[k-1][j],"◽") == 0 || strcmp(p->cases[k-1][j],"◾")==0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][j],"◾");
                    else strcpy(p->cases[k-1][j] ,"◽");
                    p->types_capture[k-1][j]=TOUR;
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
                    p->types_capture[k+1][j]=TOUR;
                    k++;
                }
                else break;
            }

            k=j;
            while (k > 0)
            {
                if (strcmp(p->cases[i][k - 1], ". ") == 0 || strcmp(p->cases[i][k - 1], "◽") == 0 || strcmp(p->cases[i][k - 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[i][k - 1], "◾");
                    else strcpy(p->cases[i][k - 1], "◽");
                    p->types_capture[i][k-1]=TOUR;
                    k--;
                }
                else break;
            }
            k=j;
            while (k < p->taille-1)
            {
                if (strcmp(p->cases[i][k + 1], ". ") == 0 || strcmp(p->cases[i][k + 1], "◽") == 0 || strcmp(p->cases[i][k + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[i][k + 1], "◾");
                    else strcpy(p->cases[i][k + 1], "◽");
                    p->types_capture[i][k+1]=TOUR;
                    k++;
                }
                else break;
            }
        break;
        };

    case CAVALIER://chacune des 8 positions est regardé pour savoir si elle est dans les bornes et si c'est une case vide.
        {          // Faire une boucle aurait été une possibilité pour éviter le code répétitif mais nous n'avons pas trouvé de solution fiable.
            if (i + 1 < p->taille && j + 2 < p->taille)
            {
                if (strcmp(p->cases[i+1][j+2],". ")==0 || strcmp(p->cases[i+1][j+2],"◽") == 0 || strcmp(p->cases[i+1][j+2],"◾")==0 )
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+1][j+2],"◾");
                    else strcpy(p->cases[i+1][j+2] ,"◽");
                    p->types_capture[i+1][j+2]=CAVALIER;
                }
            }
            if (i - 2 >= 0 && j - 1 >= 0) {
                if (strcmp(p->cases[i-2][j-1], ". ") == 0 || strcmp(p->cases[i-2][j-1], "◽") == 0 || strcmp(p->cases[i-2][j-1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i-2][j-1], "◾");
                    else strcpy(p->cases[i-2][j-1], "◽");
                    p->types_capture[i-2][j-1]=CAVALIER;
                }
            }

            // (i - 2, j + 1)
            if (i - 2 >= 0 && j + 1 < p->taille) {
                if (strcmp(p->cases[i-2][j+1], ". ") == 0 || strcmp(p->cases[i-2][j+1], "◽") == 0 || strcmp(p->cases[i-2][j+1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i-2][j+1], "◾");
                    else strcpy(p->cases[i-2][j+1], "◽");
                    p->types_capture[i-2][j+1]=CAVALIER;
                }
            }

            // (i - 1, j - 2)
            if (i - 1 >= 0 && j - 2 >= 0) {
                if (strcmp(p->cases[i-1][j-2], ". ") == 0 || strcmp(p->cases[i-1][j-2], "◽") == 0 || strcmp(p->cases[i-1][j-2], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i-1][j-2], "◾");
                    else strcpy(p->cases[i-1][j-2], "◽");
                    p->types_capture[i-1][j-2]=CAVALIER;
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
                    p->types_capture[i+1][j-2]=CAVALIER;
                }
            }

            // (i + 1, j + 2)
            if (i + 1 < p->taille && j + 2 < p->taille) {
                if (strcmp(p->cases[i+1][j+2], ". ") == 0 || strcmp(p->cases[i+1][j+2], "◽") == 0 || strcmp(p->cases[i+1][j+2], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+1][j+2], "◾");
                    else strcpy(p->cases[i+1][j+2], "◽");
                    p->types_capture[i+1][j+2]=CAVALIER;
                }
            }

            // (i + 2, j - 1)
            if (i + 2 < p->taille && j - 1 >= 0) {
                if (strcmp(p->cases[i+2][j-1], ". ") == 0 || strcmp(p->cases[i+2][j-1], "◽") == 0 || strcmp(p->cases[i+2][j-1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+2][j-1], "◾");
                    else strcpy(p->cases[i+2][j-1], "◽");
                    p->types_capture[i+2][j-1]=CAVALIER;
                }
            }

            // (i + 2, j + 1)
            if (i + 2 < p->taille && j + 1 < p->taille) {
                if (strcmp(p->cases[i+2][j+1], ". ") == 0 || strcmp(p->cases[i+2][j+1], "◽") == 0 || strcmp(p->cases[i+2][j+1], "◾") == 0) {
                    if (piece.joueur == BLANC) strcpy(p->cases[i+2][j+1], "◾");
                    else strcpy(p->cases[i+2][j+1], "◽");
                    p->types_capture[i+2][j+1]=CAVALIER;
                }
            }
            break;
        };
    case FOU://structure du code semblable à la tour mais en diagonale.
        {
            k=i;
            l=j;
            while (k>0 && l>0)
            {
                if (strcmp(p->cases[k-1][l-1],". ") == 0 || strcmp(p->cases[k-1][l-1],"◽") == 0 || strcmp(p->cases[k-1][l-1],"◾")==0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][l-1],"◾");
                    else strcpy(p->cases[k-1][l-1] ,"◽");
                    p->types_capture[k-1][l-1]=FOU;
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
                    p->types_capture[k + 1][l-1]=FOU;
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
                    p->types_capture[k-1][l + 1]=FOU;
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
                    p->types_capture[k+1][l + 1]=FOU;
                    k++;
                    l++;
                }
                else break;
            }
            break;
        };
    case DAME://Un mélange de la tour et du fou
        {
            k=i;
            while (k>0)
            {
                if (strcmp(p->cases[k-1][j],". ") == 0 || strcmp(p->cases[k-1][j],"◽") == 0 || strcmp(p->cases[k-1][j],"◾")==0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[k-1][j],"◾");
                    else strcpy(p->cases[k-1][j] ,"◽");
                    p->types_capture[k-1][j]=DAME;
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
                    p->types_capture[k + 1][j]=DAME;
                    k++;
                }
                else break;
            }

            k=j;
            while (k > 0)
            {
                if (strcmp(p->cases[i][k - 1], ". ") == 0 || strcmp(p->cases[i][k - 1], "◽") == 0 || strcmp(p->cases[i][k - 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[i][k - 1], "◾");
                    else strcpy(p->cases[i][k - 1], "◽");
                    p->types_capture[i][k - 1]=DAME;
                    k--;
                }
                else break;
            }
            k=j;
            while (k < p->taille-1)
            {
                if (strcmp(p->cases[i][k + 1], ". ") == 0 || strcmp(p->cases[i][k + 1], "◽") == 0 || strcmp(p->cases[i][k + 1], "◾") == 0)
                {
                    if (piece.joueur == BLANC) strcpy(p->cases[i][k + 1], "◾");
                    else strcpy(p->cases[i][k + 1], "◽");
                    p->types_capture[i][k + 1]=DAME;
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
                    p->types_capture[k-1][l-1]=DAME;
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
                    p->types_capture[k + 1][l-1]=DAME;
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
                    p->types_capture[k-1][l + 1]=DAME;
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
                    p->types_capture[k+1][l + 1]=DAME;
                    k++;
                    l++;
                }
                else break;
            }
                break;
            };
        case ROI: {//Nous avons fait un nouveau tableau avec les 8 coordonnées pour faire moins de lignes de code puis une boucle
            // Coordonnées autour de la pièce (8 directions)
            int dx[] = {-1, -1, -1,  0, 0, 1, 1, 1};
            int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

            for (int dir = 0; dir < 8; dir++) {
                int ni = i + dx[dir];
                int nj = j + dy[dir];

                // Vérifie que ni et nj sont dans les bornes du plateau
                if (ni >= 0 && ni < p->taille && nj >= 0 && nj < p->taille) {
                    if (strcmp(p->cases[ni][nj], ". ") == 0 || strcmp(p->cases[ni][nj], "◽") == 0 || strcmp(p->cases[ni][nj], "◾") == 0) {
                        if (piece.joueur == BLANC)
                            strcpy(p->cases[ni][nj], "◾");
                        else
                            strcpy(p->cases[ni][nj], "◽");

                        p->types_capture[ni][nj] = ROI;
                    }
                }
            }
            break;
    }

            default: break;
        }
    }