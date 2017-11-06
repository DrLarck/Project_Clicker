/**
Author : DrLarck

----------------

Role : Gère le menu du jeu grace a des boutons

Birth : 13/10/2017 (Joyeux anniversaire maman <3)

Last update : 1/11/2017

V : 0.0.3

------------------------ **/

/* C lib */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Lib */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/* Header */
#include "jeu.c"
#include "constante.h"

/* Variables */

// Structures
typedef struct Bouton
{
    int etat; // Informe de l'etat du bouton (appuyé ou relaché)
    SDL_Surface* bouton_appuye = NULL; // Image bouton appuyé
    SDL_Surface* bouton_relache = NULL; // Image bouton relaché
    SDL_Rect positionBouton; // Définit la position du bouton
};

/* SDl var */
// Surfaces
SDL_Surface *ecran = NULL;
SDL_Surface *fond_menu = NULL;
SDL_Surface *logo = NULL;

// Rect
SDL_Rect positionFondMenu;
SDL_Rect positionLogo;

// Color


// TTF


// Event
SDL_Event event;

/* Fonctions */
void jouer(SDL_Surface*);

int main ( int argc, char** argv )
{
    /* Initialisation de la SDL */
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("sprite/ico.png"), NULL); // Set l'icone

    /* Declarations & Init */
    int nonStop = 1; // Tant que != 0 alors le programme continue (while de la main)

    /* Reglage des boutons */
    Bouton boutonJouer; // Création des boutons
    Bouton boutonQuit;

    /* Demande de l'ouverture d'une fenetre aux tailles indiquées dans 'constante.h' */
    if((ecran = SDL_SetVideoMode(LARGEUR_WINDOW, HAUTEUR_WINDOW, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        /*Si la fenetre ne s'ouvre pas on inscrit l'erreur dans 'stderr.txt' */
        fprintf(stderr, "Erreur dans l'ouverture de la fenetre : %s\n\n", SDL_GetError());
        exit(EXIT_FAILURE); //On ferme
    }

    /* Nom de la fenêtre */
    SDL_WM_SetCaption("Project Clicker", NULL);

    /* Chargement du fond du menu et positionne */
    fond_menu = IMG_Load("sprite/menu_fond.png");
    positionFondMenu.x = 0;
    positionFondMenu.y = 0;

    /* Chargement du logo */
    logo = IMG_Load("sprite/logo.png");
    positionLogo.x = ecran->w / 2 - logo->w / 2;
    positionLogo.y = 30;

    /* Boutons réglage */
    boutonJouer.etat = 0; // Définit l'état de base, ici 0
    boutonQuit.etat = 0;

    boutonJouer.bouton_relache = IMG_Load("sprite/play.png"); // Définit l'apparence des boutons
    boutonJouer.bouton_appuye = IMG_Load("sprite/play.png");

    boutonQuit.bouton_appuye = IMG_Load("sprite/quit.png");
    boutonQuit.bouton_relache = IMG_Load("sprite/quit.png");

    /* Position des boutons */

    boutonJouer.positionBouton.x = ecran->w / 2 - 62; // Centre sur l'axe .x en fonction de sa largeur
    boutonJouer.positionBouton.y = 340; // Positionne sur .y

    boutonQuit.positionBouton.x = ecran->w / 2 - 62;
    boutonQuit.positionBouton.y = 400;

    /* Boucle qui maintient le programme ouvert
       permet l'affichage du menu */
    while(nonStop)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT :
            exit(EXIT_SUCCESS);
            break;

        case SDL_MOUSEBUTTONDOWN :

            /* Gestion des effets du bouton Jouer */
            if(event.button.y > 340 && event.button.y <= 340 + boutonJouer.positionBouton.h
               && event.button.x > ecran->w / 2 - 62 && event.button.x <= ecran->w / 2 - 62 + boutonJouer.positionBouton.w)
            {
                boutonJouer.etat = 1;

                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0 ,0));
                SDL_BlitSurface(fond_menu, NULL, ecran, &positionFondMenu);
                SDL_BlitSurface(boutonJouer.bouton_appuye, NULL, fond_menu, &boutonJouer.positionBouton);
                SDL_Flip(ecran);

                jouer(ecran); // Appel de la fonction Jouer();

                break;
            }

            /* Gestion des effets du bouton Quitter */
            if(event.button.y > 400 && event.button.y <= 400 + boutonQuit.positionBouton.h
               && event.button.x > ecran->w / 2 - 62 && event.button.x <= ecran->w / 2 - 62 + boutonQuit.positionBouton.w)
            {
                boutonQuit.etat = 1;

                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                SDL_BlitSurface(fond_menu, NULL, ecran, &positionFondMenu);
                SDL_BlitSurface(boutonQuit.bouton_appuye, NULL, fond_menu, &boutonQuit.positionBouton);
                SDL_Flip(ecran);

                nonStop = 0; // Ferme l'application

                break;
            }
            break;
        }

            /* Si on appui sur ECHAP */
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE :
                nonStop = 0;
                break;
                default : break;
            }

            /* Affichage du fond */
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            SDL_BlitSurface(fond_menu, NULL, ecran, &positionFondMenu);
            SDL_BlitSurface(logo, NULL, ecran, &positionLogo);

            /* Affichage des boutons */
            SDL_BlitSurface(boutonJouer.bouton_relache, NULL, ecran, &boutonJouer.positionBouton);
            SDL_BlitSurface(boutonQuit.bouton_relache, NULL, ecran, &boutonQuit.positionBouton);

            /* Affichage du Logo */
            SDL_BlitSurface(logo, NULL, ecran, &positionLogo);

            /* Flip */
            SDL_Flip(ecran);

    } // Fin boucle principale
    return EXIT_SUCCESS;
} // Fin main


