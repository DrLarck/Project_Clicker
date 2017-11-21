/**
Author : DrLarck

----------------

Role : Gestion du shop

Birth : 01/11/2017

Last update : 21/11/2017

V : 0.1.5

------------------------ **/
#ifndef SHOP_C_INCLUDED
#define SHOP_C_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "constante.h"

/* Fonctions */
void Reset_Compteur_Clic(unsigned long, SDL_Surface *screen);//Reset le nbr de clics dans shop

void jouer(SDL_Surface *ecran); // Fonction jouer qui ouvre jeu.c
    // Péon
void Init_Peon_Files(unsigned int, unsigned int); // Initialise les fichiers du Peon, recoit Peon.stat && Peon.tick
void Reset_Compteur_Peon(unsigned int, SDL_Surface*); // Reset le nbr de Peon a afficher
void Open_Peon_Save(void); // Ouvre le nbr de péons
    // Péon en chef
void Init_PeonChef_Files(unsigned int, unsigned int); // Recoit PeonChef.stat et PeonChef.tick
void Reset_Compteur_PeonChef(unsigned int, SDL_Surface*);
void Open_PeonChef_Save(void);

/* File */
// Joueur
FILE *playerClic = NULL; // Appelle du nombre de clics du joueur

    //Peon
FILE *peonQt = NULL;
FILE *peonStat = NULL;
FILE *peonTime = NULL;
FILE *PeonSauvegarde = NULL;
    // Péon_Chef
FILE *peonChefQt = NULL;
FILE *peonChefStat = NULL;
FILE *peonChefTime = NULL;
FILE *PeonChefSauvegarde = NULL;

/* Var */
int continuer; // Maintient le programme ouvert
int checkClic = 0; // Vérifie le clic (1 si clic, 0 sinon)
unsigned int getPeonQt;
unsigned int getPeonChefQt;
unsigned long playerClicStock;

// Textes
char compteurClicTexte_Shop[500] = "";
    // Items
char compteurItem_Peon[500] = "";
char compteurItem_PeonChef[500] = "";

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
SDL_Surface *bouton_Jouer = NULL;
    // Peon
SDL_Surface *peon_ico = NULL;
    // PeonChef
SDL_Surface *peonChef_ico = NULL;
SDL_Surface *peonchef_ico_nope = NULL;
SDL_Surface *peonchef_ico_appuye = NULL;

    // Texte
            // Peon
SDL_Surface *peon_texte = NULL;
SDL_Surface *texte_ItemPeon = NULL;
            // Peon_Chef
SDL_Surface *peonChef_texte = NULL;
SDL_Surface *texte_ItemPeonChef = NULL;

SDL_Surface *joueurClic_texte = NULL;

// Rect
SDL_Rect positionFondShop;
SDL_Rect bouton_JouerPos;
    // Peon
SDL_Rect peon_pos;
    // Peon_Chef
SDL_Rect peonChef_pos;
    // Texte
        //Peon
SDL_Rect peon_textePos;
SDL_Rect texte_ItemPeon_pos;
        //Peon_Chef
SDL_Rect peonChef_textePos;
SDL_Rect texte_ItemPeonChef_pos;

SDL_Rect joueurClicTexte_pos;

// Event
SDL_Event shopEvent;

// TTF
TTF_Font *shop_police = NULL; // Police du shop
TTF_Font *joueurClic_police = NULL; // Police du compteur de clic du joueur

// Color
SDL_Color shop_CouleurText = {0,0,0};

void Shop(SDL_Surface *ecran)
{

    // Ouvre le nombre d'item
        // Peon
    Open_Peon_Save();
    //
        // Peon en chef
    Open_PeonChef_Save();
    //

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
    //

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
    //
    // Péon
    struct Item Peon; // 1 Clic/Peon/3sec
    Peon.qt = getPeonQt; // Quantité de départ
    Peon.stat = 1; // Clic bonus
    Peon.tick = 10000; // Temps entre 2 clic auto 10s
    //
    // Péon en Chef
    struct Item Peon_Chef;
    Peon_Chef.qt = getPeonChefQt;
    Peon_Chef.stat = 1;
    Peon_Chef.tick = 8500; // 8.5s
    //
    //

/** PEON : Initialisation des fichiers **/
Init_Peon_Files(Peon.stat, Peon.tick); // Envoie des stats et du tick
/** PEON : Initialisation des fichiers **/
Init_PeonChef_Files(Peon_Chef.stat, Peon_Chef.tick);

        // Icone 50*50 = Intervale de 10px entre chaque
            // Peon
        peon_ico = IMG_Load("sprite/item/peon.png");
        peon_pos.x = 5;
        peon_pos.y = 5;
            // Peon_Chef
        peonChef_ico = IMG_Load("sprite/item/peon_chef.png");
        peonchef_ico_nope = IMG_Load("sprite/item/peon_chefNope.png");
        peonchef_ico_appuye = IMG_Load("sprite/item/peon_chefAppuye.png");
        peonChef_pos.x = 5;
        peonChef_pos.y = 60;


        /** Textes **/
        // Compteur de clic du joueur.
        sprintf(compteurClicTexte_Shop, "Clics : %ld", playerClicStock); // Inscrit le nbr clics

        joueurClic_police = TTF_OpenFont("font/calibri.ttf", 20); // Taille du compteur de clic dans shop
        joueurClic_texte = TTF_RenderText_Blended(joueurClic_police, compteurClicTexte_Shop, shop_CouleurText);
        joueurClicTexte_pos.x = ecran->w / 2 - joueurClic_texte->w / 2;
        joueurClicTexte_pos.y = 495;

        //Affichage des infos de Peon
        shop_police = TTF_OpenFont("font/calibri.ttf", 14); // Taille du prix
        peon_texte = TTF_RenderText_Blended(shop_police, "Peon : 100 = +1/10s", shop_CouleurText); // Texte Peon
        peon_textePos.x = 60;
        peon_textePos.y = 20;
            //Affichage du nbr de Peons
        sprintf(compteurItem_Peon, "Own : %d", Peon.qt);
        texte_ItemPeon = TTF_RenderText_Blended(shop_police, compteurItem_Peon, shop_CouleurText);
        texte_ItemPeon_pos.x = 60;
        texte_ItemPeon_pos.y = 33;

        //Affichage des infos de Peon_Chef
        peonChef_texte = TTF_RenderText_Blended(shop_police, "Chef Peon : 500 = +1/8,5s", shop_CouleurText);
        peonChef_textePos.x = 60;
        peonChef_textePos.y = 70;
            //Affichage du nbr de Peons
        sprintf(compteurItem_PeonChef, "Own : %d", getPeonChefQt);
        texte_ItemPeonChef = TTF_RenderText_Blended(shop_police, compteurItem_PeonChef, shop_CouleurText);
        texte_ItemPeonChef_pos.x = 60;
        texte_ItemPeonChef_pos.y = 83;
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

                    Reset_Compteur_Clic(playerClicStock, ecran); // Reset des affichages
                    Reset_Compteur_Peon(Peon.qt, ecran); // Envoie la nouvelle quantité

                    checkClic = 1; // Le joueur clique
               }
               //
               // Peon_Chef
               if(playerClicStock >= 500 && SDL_BUTTON_LEFT && checkClic == 0
               && shopEvent.button.y >= 60 && shopEvent.button.y <= 60 + peonChef_pos.h
               && shopEvent.button.x > 25 - 25
               && shopEvent.button.x <= 25 - 25 + peonChef_pos.w)
               {
                   getPeonChefQt++;
                   peonChefQt = fopen("file/item/peon_chef.qt", "w");
                        if(peonChefQt != NULL)
                        {
                            fprintf(peonChefQt, "%d", getPeonChefQt);
                            fclose(peonChefQt);
                        }
                            else
                            {
                                exit(EXIT_FAILURE);
                            }
                    playerClicStock -= PEON_CHEF_PRIX;
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

                    Reset_Compteur_Clic(playerClicStock, ecran); // Reset des affichages
                    Reset_Compteur_PeonChef(getPeonChefQt, ecran);
                    checkClic = 1;
               }

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
        // Images
        SDL_BlitSurface(fond_shop, NULL, ecran, &positionFondShop);
        SDL_BlitSurface(bouton_Jouer, NULL, ecran, &bouton_JouerPos);
            // Items
        SDL_BlitSurface(peon_ico, NULL, ecran, &peon_pos);
        SDL_BlitSurface(peonChef_ico, NULL, ecran, &peonChef_pos);

        // Textes
            // Item
        SDL_BlitSurface(peon_texte, NULL, ecran, &peon_textePos);
        SDL_BlitSurface(texte_ItemPeon, NULL, ecran, &texte_ItemPeon_pos);
        SDL_BlitSurface(peonChef_texte, NULL, ecran, &peonChef_textePos);
        SDL_BlitSurface(texte_ItemPeonChef, NULL, ecran, &texte_ItemPeonChef_pos);
        //
        SDL_BlitSurface(joueurClic_texte, NULL, ecran, &joueurClicTexte_pos);

        /* Flip ecran */
        SDL_Flip(ecran);

    } // Fin boucle principale

} // Fin de la fonction Shop()

void Reset_Compteur_Clic(unsigned long NewClickValue, SDL_Surface *screen) // Reset des affichages
{
    /* Reset */
    SDL_FreeSurface(joueurClic_texte);
    /* Inscription de la nouvelle valeur */
    sprintf(compteurClicTexte_Shop, "Clic : %ld", NewClickValue);
    joueurClic_texte = TTF_RenderText_Blended(joueurClic_police, compteurClicTexte_Shop,
                                                shop_CouleurText);
    /* Blit de la nouvelle surface */
    SDL_BlitSurface(joueurClic_texte, NULL, screen, &joueurClicTexte_pos);

    SDL_Flip(screen);

} // Fin de la fonction Reset_Compteur_Clic

                                    /** Péon **/
void Reset_Compteur_Peon(unsigned int NewPeonValue, SDL_Surface *ecran) // Reset des affichages
{
    /* Reset */
    SDL_FreeSurface(texte_ItemPeon);
    /* Inscription de la nouvelle valeur */
    sprintf(compteurItem_Peon, "Own : %d", NewPeonValue);
    texte_ItemPeon = TTF_RenderText_Blended(shop_police, compteurItem_Peon,
                                                shop_CouleurText);
    /* Blit de la nouvelle surface */
    SDL_BlitSurface(texte_ItemPeon, NULL, ecran, &texte_ItemPeon_pos);

    SDL_Flip(ecran);

} // Fin Reset_Compteur_Peon()

void Init_Peon_Files(unsigned int stat, unsigned int tick)
{
    /** PEON : Initialisation des fichiers **/
    peonStat = fopen("file/item/peon.st", "w"); // Inscrit les stat du peon.
        if(peonStat != NULL)
        {
            fprintf(peonStat, "%d", stat);
            fclose(peonStat);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

    peonTime = fopen("file/item/peon.time", "w"); // Inscrit les secondes avant tick du Peon.
        if(peonTime != NULL)
        {
            fprintf(peonTime, "%d", tick);
            fclose(peonTime);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

} // Fin Init_Peon_Files

void Open_Peon_Save(void)
{
    /** Sauvegarde de Peon **/
    PeonSauvegarde = fopen("file/item/peon.qt", "r");
    if(PeonSauvegarde != NULL)
    {
        fscanf(PeonSauvegarde, "%d", &getPeonQt);
        fclose(PeonSauvegarde);
    }

} // Fin Open_Peon_Save
                                        /** Peon_Chef **/
void Init_PeonChef_Files(unsigned int stat_peonChef, unsigned int tick_peonChef)
{
    /** Peon_Chef : Initialisations files **/
    peonChefStat = fopen("file/item/peon_chef.stat", "w");
        if(peonChefStat != NULL)
        {
            fprintf(peonChefStat, "%d", stat_peonChef);
            fclose(peonChefStat);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

    peonChefTime = fopen("file/item/peon_chef.time", "w");
        if(peonChefTime != NULL)
        {
            fprintf(peonChefTime, "%d", tick_peonChef);
            fclose(peonChefTime);
        }
            else
            {
                exit(EXIT_FAILURE);
            }

} // Fin Init_PeonChef_Files

void Open_PeonChef_Save(void)
{
    /** Save de Peon_Chef **/
    PeonChefSauvegarde = fopen("file/item/peon_chef.qt", "r");
        if(PeonChefSauvegarde != NULL)
        {
            fscanf(PeonChefSauvegarde, "%d", &getPeonChefQt); // Initi le nbr de péon_chef
            fclose(PeonChefSauvegarde);
        }

} // Fin Open_PeonChef_Save

void Reset_Compteur_PeonChef(unsigned int NewPeonChefValue, SDL_Surface *ecran)
{
    /* Reset */
    SDL_FreeSurface(texte_ItemPeonChef);
    /* Inscription de la nouvelle valeur */
    sprintf(compteurItem_PeonChef, "Own : %d", NewPeonChefValue);
    texte_ItemPeonChef = TTF_RenderText_Blended(shop_police, compteurItem_PeonChef,
                                                shop_CouleurText);
    /* Blit de la nouvelle surface */
    SDL_BlitSurface(texte_ItemPeonChef, NULL, ecran, &texte_ItemPeonChef_pos);

    SDL_Flip(ecran);

} //Fin Reset_Compteur_PeonChef
#endif // SHOP_C_INCLUDED
