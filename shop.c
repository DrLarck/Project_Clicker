/**
Author : DrLarck

----------------

Role : Gestion du shop

Birth : 1/11/2017

Last update : 06/11/2017

V : 0.0.6

------------------------ **/
#ifndef SHOP_C_INCLUDED
#define SHOP_C_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>

/* Functions */
void jouer(SDL_Surface *ecran);

/* Var */
int continuer; // Maintient le programme ouvert

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

// Rect
SDL_Rect positionFondShop;

SDL_Rect peon_pos;
SDL_Rect peon_textePos;

// Event
SDL_Event shopEvent;

// TTF
TTF_Font *shop_police; // Police du shop

// Color
SDL_Color shop_CouleurText = {0,0,0};

void Shop(SDL_Surface *ecran)
{
    /* Fond */
    fond_shop = IMG_Load("sprite/menu_fond.png");
    positionFondShop.x = 0;
    positionFondShop.y = 0;

    /* Init */
    continuer = 1; // Gère la fermeture de programme
    //
    //
    struct Item Peon; /** 1 Clic/Peon/3sec **/
    Peon.qt = 0; // Quantité de départ
    Peon.stat = 1; // Clic bonus
    Peon.tick = 10000; // Temps entre 2 clic auto
    //

    //
    //

    /* Fichiers */
    //Peon
    FILE *peonQt = NULL;
    FILE *peonStat = NULL;
    FILE *peonTime = NULL;
    FILE *openPeonQt = NULL;
    //

    /** PEON : Initialisation des fichiers **/
    peonQt = fopen("file/item/peon.qt", "w"); // Inscrit la quantité de péon que possède le joueur.
        if(peonQt != NULL)
        {
            fprintf(peonQt, "%d", Peon.qt);
            fclose(peonQt);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

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

        //Prix
        Peon.prix = 100;
        shop_police = TTF_OpenFont("font/calibri.ttf", 14); // Taille du prix

        peon_texte = TTF_RenderText_Blended(shop_police, "Peon : 100 = +1/10s", shop_CouleurText); // Texte Peon

        peon_textePos.x = 60;
        peon_textePos.y = 20;


    /** **/

    while(continuer)
    {
        SDL_PollEvent(&shopEvent);

        /* Fermeture avec croix */
        switch(shopEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN :
            if()
            Peon.qt += 1;
            peonQt = fopen("file/item/peon.qt", "w");
                if(peonQt != NULL)
                {
                  fprintf(peonQt, "%d", Peon.qt);
                  fclose(peonQt)  ;
                }
                    else
                    {
                        exit(EXIT_FAILURE);
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

        case SDLK_j: // Si -J retourne sur le jeu
            jouer(ecran);
            break;

        default : break;
        }

        /* Reset de l'ecran */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));

        /* Blit des surfaces */
        SDL_BlitSurface(fond_shop, NULL, ecran, &positionFondShop);

        SDL_BlitSurface(peon_ico, NULL, ecran, &peon_pos);
        SDL_BlitSurface(peon_texte, NULL, ecran, &peon_textePos);

        /* Flip ecran */
        SDL_Flip(ecran);

    } // Fin boucle principale

} // Fin de la fonction Shop()

#endif // SHOP_C_INCLUDED
