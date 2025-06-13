
#include <stdio.h>
#include "board.h"
#include "menu.h"

#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
/**
 * @brief Affiche le menu principal du jeu et lit le choix de l'utilisateur.
 *
 * Propose à l'utilisateur de démarrer une nouvelle partie, de reprendre une partie sauvegardée ou de quitter le jeu.
 * Vérifie que l'utilisateur entre une valeur correcte (1, 2 ou 3).
 *
 * @return int Le choix de l'utilisateur :
 * - 1 pour démarrer une partie
 * - 2 pour reprendre une partie
 * - 3 pour quitter
 */
int menu() {
    int rep,rep2;
    printf("-----------Menu-----------\n 1) Demarrer une partie\n 2) Reprendre une partie\n 3) Quitter\n"); //affichage du menu
    scanf("%d", &rep);
    while(rep <1 || rep>3) {
        printf("Veuillez entrer votre choix: 1,2 ou 3\n"); //message d'erreur
        scanf("%d", &rep);
    }
    return rep;
}
/**
 * @brief Permet à l'utilisateur de choisir le mode de jeu et la taille du plateau.
 *
 * Deux modes de jeu sont disponibles : conquête ou connecté. Ensuite, l'utilisateur choisit une taille de plateau comprise entre 6x6 et 12x12.
 * Les entrées sont validées pour éviter les valeurs incorrectes.
 *
 * @param size Pointeur vers un entier dans lequel sera stockée la taille du plateau choisie.
 * @return int Le mode de jeu choisi :
 * - 1 pour Conquête
 * - 2 pour Connecté
 */
int mode(int *size) {
    int choix;
    printf("Quel mode de jeu voulez vous choisir ?\n 1) Conquete\n 2) Connecte\n");
    scanf("%d",&choix);
    while(choix <1 || choix>2) {
        printf("Veuillez entrer votre choix: entre 1 et 3\n"); //message d'erreur
        scanf("%d", &choix);
    }
    printf("Quelle taille d'echiquier voulez-vous ?\n (entre 6x6 et 12x12)\n");
    scanf("%d", size);
    while(*size <6 || *size>12) {
        printf("Veuillez entrer votre choix entre 6 et 12\n"); //message d'erreur
        scanf("%d", size);
    }
    return choix;
}
/**
 * @brief Affiche le menu de jeu pour un joueur et récupère son choix.
 *
 * Ce menu s'affiche à chaque tour. Il permet au joueur courant (noir ou blanc) de poser une pièce, d’abandonner ou de sauvegarder la partie.
 * La saisie est vérifiée pour garantir une valeur correcte.
 *
 * @param j Joueur courant (BLANC ou NOIR).
 * @return int Le choix du joueur :
 * - 1 pour poser une pièce
 * - 2 pour abandonner
 * - 3 pour sauvegarder la partie
 */
int menu_jeu(Joueur j){
    int rep;
    if (j==1) printf("C'est au tour des blancs\n");
    else printf("C'est au tour des noirs\n");

    printf("Que voulez vous faire ? \n");
    printf("1) Poser une pièce \n");
    printf("2) Abandonner \n");
    printf("3) Sauvegarder la partie \n");
    scanf("%d", &rep);
    while (rep <1 || rep>3)
    {
        printf("Veuillez entrer votre choix: 1,2 ou 3\n");
        scanf("%d", &rep);
    }
    if (rep == 3) printf("Sauvegarde en cours...\n");
    //fonction de sauvegarde
    return rep;
}

/**
 * @brief Affiche un message sur l'utilisation des symboles unicode dans le programme.
 *
 * Ce programme affichant des symboles unicode, certaines polices d'écritures ne les prennent pas en charge
 * ou correctement sur les symboles utilisés, notamment les couleurs et le pion blanc.
 * La fonction demande également si l'utilisateur veut ou non revoir ce message ou prochain lancement.
 * Il stocke son choix dans un fichier .txt qu'il consulte avant d'afficher le message.
 *
 */
void message()
{
    FILE *config = fopen("config.txt", "r");
    char buffer[10];

    if (config != NULL) {
        fgets(buffer, sizeof(buffer), config);
        fclose(config);
        if (strcmp(buffer, "no\n") == 0 || strcmp(buffer, "no") == 0) {
            return; // Ne pas afficher le message
        }
    }

    printf("Bienvenue dans notre programme !\n\nDes caractères unicodes vont être affichés pour symboliser les pièces d'échecs et les cases capturées.\n");
    printf("Pour bénéficier d'une expérience optimale, veuillez vous assurer que la police d'écriture de votre console ou de votre terminal est adapté à l'affichage de ceux-ci.\n\n");
    printf("Le code a été testé pour s'afficher de manière optimale dans un terminal Linux. \n");
    printf("Certaines polices affichent parfois les couleurs inverses de ce que dit le programme et le pion blanc est parfois représenté différement\n\n");
    printf("Merci de votre compréhension ! \n");

#ifdef WIN32//commandes différentes selon l'OS de l'utilisateur
    Sleep(5000);
#else
    sleep(5);
#endif

    printf("Souhaitez-vous revoir ce message au prochain lancement ? (o/n) : ");
    char rep;
    scanf(" %c", &rep);
    config = fopen("config.txt", "w");
    if (config != NULL) {
        if (rep == 'n' || rep == 'N') {
            fprintf(config, "no\n");
        } else {
            fprintf(config, "yes\n");
        }
        fclose(config);
    }
}