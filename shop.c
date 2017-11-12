/**
Author : DrLarck

----------------

Role : Gestion du shop

Birth : 1/11/2017

Last update : 12/11/2017

V : 0.0.9

------------------------ **/
#ifndef SHOP_C_INCLUDED
#define SHOP_C_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>

/* Functions */
void jouer(SDL_Surface *ecran);

void ItemSave_Peon(unsigned int);

/* File */
FILE *PeonSauvegarde = NULL;

/* Var */
int continuer; // Maintient le programme ouvert

int checkClic = 0; // Vérifie le clic (1 si clic, 0 sinon)

unsigned int getPeonQt;

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
    /** Sauvegarde de Peon **/
    PeonSauvegarde = fopen("file/peon_save.lrk", "r");
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
    //

    //
    //

    /* Fichiers */
    //Peon
    FILE *peonQt = NULL;
    FILE *peonStat = NULL;
    FILE *peonTime = NULL;

    FILE *checkPeonQt = NULL;
    //
    //

    struct Item Peon; /** 1 Clic/Peon/3sec **/
    Peon.qt = getPeonQt; // Quantité de départ
    Peon.stat = 1; // Clic bonus
    Peon.tick = 1000; // Temps entre 2 clic auto
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
            if(SDL_BUTTON_LEFT && checkClic == 0
               && shopEvent.button.y >= 5 && shopEvent.button.y <= 5 + peon_pos.h
               && shopEvent.button.x > 25 - 25
               && shopEvent.button.x <= 25 - 25 + peon_pos.w)
            // Si clic sur l'icone peon
               {
                    Peon.qt += 1;
                    getPeonQt++;
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
                    checkClic = 1; // Le joueur clique
               }

               // Si clic sur Jouer
               if(SDL_BUTTON_LEFT && shopEvent.button.y >= 520 && shopEvent.button.y <= 520 + bouton_JouerPos.h
               && shopEvent.button.x > ecran->w / 2 - bouton_Jouer->w / 2
               && shopEvent.button.x <= ecran->w / 2 - bouton_Jouer->w / 2 + bouton_JouerPos.w)
               {
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
                   jouer(ecran);
               }

        break;

        case SDL_QUIT: // Si CROIX = Ferme l'app
            exit(EXIT_SUCCESS);
            break;

        case SDL_MOUSEBUTTONUP :
            if(SDL_BUTTON_LEFT)
            {
                checkClic = 0; // Le joueur ne clique plus
            }

        default : break;

        }

        switch(shopEvent.key.keysym.sym)
        {
        case SDLK_ESCAPE : // Si ECHAP = ferme l'app
            exit(EXIT_SUCCESS);
            break;

        default : break;
        }

        ItemSave_Peon(getPeonQt); // Envoi du nombre de Péon pour sauvegarde

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

void ItemSave_Peon(unsigned int PeonStock)
{
    /* Fichiers */
    PeonSauvegarde = fopen("file/peon_save.lrk", "w");
    if(PeonSauvegarde != NULL)
    {
        fprintf(PeonSauvegarde, "%d", getPeonQt);
        fclose(PeonSauvegarde);
    }
    else
    {
        exit(EXIT_FAILURE);
    }


} // Fin de la fonction ItemSave_Peon();

#endif // SHOP_C_INCLUDED
