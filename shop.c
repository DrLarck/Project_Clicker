/**
Author : DrLarck

----------------

Role : Gestion du shop

Birth : 1/11/2017

Last update : 13/11/2017

V : 0.1.0

------------------------ **/
#ifndef SHOP_C_INCLUDED
#define SHOP_C_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "constante.h"

/* Functions */
void jouer(SDL_Surface *ecran);

/* File */
// Joueur
FILE *playerClic = NULL; // Appelle du nombre de clics du joueur

//Peon
FILE *peonQt = NULL;
FILE *peonStat = NULL;
FILE *peonTime = NULL;

FILE *PeonSauvegarde = NULL;

/* Var */
int continuer; // Maintient le programme ouvert

int checkClic = 0; // Vérifie le clic (1 si clic, 0 sinon)

unsigned int getPeonQt;
unsigned long playerClicStock;

// struct
struct Item
{
    unsigned int qt; // Quantité
    unsigned int stat; // Clic/tick
    unsigned int tick; // Temps avant clic (1000 pour 1sec avant clic)
    unsigned long prix;
    char texte;
};

// Pointeur
/* SDL's var */
// Surface
SDL_Surface *fond_shop = NULL;

SDL_Surface *peon_ico = NULL;
SDL_Surface *peon_texte = NULL;
SDL_Surface *bouton_Jouer = NULL;

// Rect
SDL_Rect positionFondShop;

SDL_Rect peon_pos;
SDL_Rect peon_textePos;
SDL_Rect bouton_JouerPos;

// Event
SDL_Event shopEvent;

// TTF
TTF_Font *shop_police; // Police du shop

// Color
SDL_Color shop_CouleurText = {0,0,0};

void Shop(SDL_Surface *ecran)
{
    /** Ouverture de la sauvegarde clic **/
    playerClic = fopen("file/c_save.lrk", "r"); // Stocke le nombre de clic que possède le joueur dans playerClicStock;
        if(playerClic != NULL)
        {
            fscanf(playerClic, "%ld", &playerClicStock);
            fclose(playerClic);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

    /** Sauvegarde de Peon **/
    PeonSauvegarde = fopen("file/item/peon.qt", "r");
    if(PeonSauvegarde != NULL)
    {
        fscanf(PeonSauvegarde, "%d", &getPeonQt);
        fclose(PeonSauvegarde);
    }

    /* Fond */
    fond_shop = IMG_Load("sprite/menu_fond.png");
    positionFondShop.x = 0;
    positionFondShop.y = 0;

    /* Images */
    // Bouton Jouer
    bouton_Jouer = IMG_Load("sprite/play.png");

    bouton_JouerPos.x = ecran->w / 2 - bouton_Jouer->w / 2;
    bouton_JouerPos.y = 520;


    /* Init */
    continuer = 1; // Gère la fermeture de programme

    /* Fichiers */
    //
    //
    struct Item Peon; // 1 Clic/Peon/3sec
    Peon.qt = getPeonQt; // Quantité de départ
    Peon.stat = 1; // Clic bonus
    Peon.tick = 10000; // Temps entre 2 clic auto
    //
    //

    /** PEON : Initialisation des fichiers **/
    peonStat = fopen("file/item/peon.st", "w"); // Inscrit les stat du peon.
        if(peonStat != NULL)
        {
            fprintf(peonStat, "%d", Peon.stat);
            fclose(peonStat);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

    peonTime = fopen("file/item/peon.time", "w"); // Inscrit les secondes avant tick du Peon.
        if(peonTime != NULL)
        {
            fprintf(peonTime, "%d", Peon.tick);
            fclose(peonTime);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

        // Icone
        peon_ico = IMG_Load("sprite/item/peon.png");

        peon_pos.x = 5;
        peon_pos.y = 5;

        //Affichage des infos de Peon
        shop_police = TTF_OpenFont("font/calibri.ttf", 14); // Taille du prix
        peon_texte = TTF_RenderText_Blended(shop_police, "Peon : 100 = +1/10s", shop_CouleurText); // Texte Peon
        peon_textePos.x = 60;
        peon_textePos.y = 20;

    while(continuer)
    {
        SDL_PollEvent(&shopEvent);

        /* Fermeture avec croix */
        switch(shopEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN :
            // Peon
            if(playerClicStock >= 100 && SDL_BUTTON_LEFT && checkClic == 0
               && shopEvent.button.y >= 5 && shopEvent.button.y <= 5 + peon_pos.h
               && shopEvent.button.x > 25 - 25
               && shopEvent.button.x <= 25 - 25 + peon_pos.w)
            // Si clic sur l'icone peon et playerClicStock >= 100
               {
                    Peon.qt += 1;
                    getPeonQt++;
                    peonQt = fopen("file/item/peon.qt", "w"); // Incrémente peon.qt
                        if(peonQt != NULL)
                        {
                            fprintf(peonQt, "%d", Peon.qt);
                            fclose(peonQt)  ;
                        }
                            else
                            {
                                exit(EXIT_FAILURE);
                            }

                    playerClicStock -= PEON_PRIX; // Soustracion du prix

                    playerClic = fopen("file/c_save.lrk", "w"); // Inscrit la nouvelle valeur de c_save.lrk
                        if(playerClic != NULL)
                        {
                            fprintf(playerClic, "%ld", playerClicStock);
                            fclose(playerClic);
                        }
                            else
                            {
                                exit(EXIT_FAILURE);
                            }


                    checkClic = 1; // Le joueur clique
               }
               //
               //

               // Si clic sur Jouer
               if(SDL_BUTTON_LEFT && shopEvent.button.y >= 520 && shopEvent.button.y <= 520 + bouton_JouerPos.h
               && shopEvent.button.x > ecran->w / 2 - bouton_Jouer->w / 2
               && shopEvent.button.x <= ecran->w / 2 - bouton_Jouer->w / 2 + bouton_JouerPos.w)
               {
                   jouer(ecran);
               }

        break;

        case SDL_MOUSEBUTTONUP :
            if(SDL_BUTTON_LEFT)
            {
                checkClic = 0; // Le joueur ne clique plus
            }
            break;

        case SDL_QUIT: // Si CROIX = Ferme l'app
            exit(EXIT_SUCCESS);
            break;

        default : break;

        }

        switch(shopEvent.key.keysym.sym)
        {
        case SDLK_ESCAPE : // Si ECHAP = ferme l'app
            exit(EXIT_SUCCESS);
            break;

        default : break;
        }
        /* Reset de l'ecran */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));

        /* Blit des surfaces */
        SDL_BlitSurface(fond_shop, NULL, ecran, &positionFondShop);

        SDL_BlitSurface(peon_ico, NULL, ecran, &peon_pos);
        SDL_BlitSurface(peon_texte, NULL, ecran, &peon_textePos);
        SDL_BlitSurface(bouton_Jouer, NULL, ecran, &bouton_JouerPos);

        /* Flip ecran */
        SDL_Flip(ecran);

    } // Fin boucle principale

} // Fin de la fonction Shop()
#endif // SHOP_C_INCLUDED
