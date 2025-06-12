#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "board.h"
#include "connecte.h"
#include "sauvegarde.h"
#include "conquete.h"


/**
 * @brief Fonction principale du programme du jeu.
 *
 * Affiche le menu, gère le choix de l’utilisateur (nouvelle partie, chargement, quitter),
 * initialise les structures nécessaires et lance le jeu en mode "conquête" ou "connecté".
 *
 * @return int 0 si exécution correcte, 1 en cas d'erreur ou si l'utilisateur quitte.
 */
int main(void) {
    srand(time(0));

    int choix_menu, taille_plateau, joueur_actuel, mode_jeu;
    Plateau p;
    CompteurPiece cpj1, cpj2;

    message();//affiche un message pour l'utilisateur sur l'utilisation des symboles unicode

    choix_menu = menu();

    if (choix_menu != 3) {
        if (choix_menu == 1) {//si on commence on nouvelle partie on demande à l'utilisateur ce qu'il veut faire et on initialise les plateaux, compteurs de pièces...
            mode_jeu = mode(&taille_plateau);
            joueur_actuel = rand()% 2;
            p.taille = taille_plateau;
            initialiser_plateau(&p);
            initialiser_tableau_capture(&p);
            initialiser_compteur(&cpj1);
            initialiser_compteur(&cpj2);
        } else {//si on charge une partie la fonction chargement() le fait toute seule
            if (chargement(&p, &joueur_actuel, &mode_jeu, &cpj1, &cpj2) == -1) {
                printf("Erreur lors du chargement de la partie.\n");
                return 1;
            }
            printf("Partie chargée avec succès !\n");
            afficher_plateau(p);
        }

        if (mode_jeu == 1) conquete(&p, joueur_actuel, cpj1, cpj2);
        else connecte(&p, joueur_actuel, cpj1, cpj2);

        // Libération mémoire
        liberer_plateau(&p);
    } else {
        printf("Au revoir !\n");
        return 1;
    }

    return 0;
}