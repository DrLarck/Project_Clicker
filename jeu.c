/**
Author : DrLarck

----------------

Role : Gere le jeu

Birth : 13/10/2017 (Joyeux anniversaire maman <3)

Last update : 06/11/2017

V : 0.0.7

------------------------ **/
#ifndef JEU_C_INCLUDED
#define JEU_C_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "shop.c"

/* Functions */
unsigned int Sauvegarder(unsigned int); // Fonction qui permettra la sauvegarde


/* Variables */
int nonStop = 1; // Permet de maintenir le programme ouvert
int verifClic = 0; // Si le joueur effectue un clic += 1
int versionTier_1, versionTier_2, versionTier_3;

unsigned int clicStock; // Stock les clics de c_save.lrk

char compteurVersionTexte[50] = "";
char compteurClicTexte[50] = "";

// Temps
int tempsActuel = 0, tempsPrec = 0;

// Struct
typedef struct Clic
{
  unsigned int clicActuel;
  unsigned int clicPrec;;
};

struct AutoClic
{
    unsigned int qt;
    unsigned int stat;
    unsigned int tick;
};

struct Ticks
{
    unsigned int TickActu;
    unsigned int TickPrec;
};

// Pointeurs


/* SDL's var */
// Surface
SDL_Surface *texteClicSurface = NULL; // Stock le compteur de clic
SDL_Surface *fond_jeu = NULL;
SDL_Surface *bouton_Shop = NULL;

SDL_Surface *mobSprite = NULL;

SDL_Surface *texteVersion = NULL; // Numéro de version

// Rect
SDL_Rect positionTexteClic;
SDL_Rect positionTexteVersion;
SDL_Rect positionFondJeu;
SDL_Rect mobPosition;
SDL_Rect bouton_shopPos;

// Event
SDL_Event jeuEvent;

// TTF
TTF_Font *police; // Stock la police d'écriture
TTF_Font *policeVersion;

// color
SDL_Color couleurTextClic = {0,0,0};

void jouer(SDL_Surface *ecran)
{
    /* Fichiers Sauvegarde */
    FILE *checkClicSave = NULL;

    checkClicSave = fopen("file/c_save.lrk", "r"); // Ouverture en mode lecture de c_save
        if(checkClicSave != NULL)
        {
            fscanf(checkClicSave, "%d", &clicStock); // Stock le nombre inscrit
            fclose(checkClicSave);
        }
        else
        {
            exit(EXIT_FAILURE);
        }

    /* Init */
    struct Clic PlayerClic;

    PlayerClic.clicActuel = clicStock; // Stock les clics pour la sauvegarde
    PlayerClic.clicPrec = 0;

    versionTier_1 = 0;   /* Cumule le numéro */
    versionTier_2 = 0;   /* de version, /10  */
    versionTier_3 = 6;   /* par tier.        */

    /* Chargement de l'image de fond */
    fond_jeu = IMG_Load("sprite/menu_fond.png");

    positionFondJeu.x = 0;
    positionFondJeu.y = 0;

    /* Chargement du texte */
    TTF_Init();
    police = TTF_OpenFont("font/calibri.ttf", 30);

    policeVersion = TTF_OpenFont("font/calibri.ttf", 14); // Créer la police de la version

    /* Inscrit le nombre de clics dans la chaine de char à afficher */
    sprintf(compteurClicTexte, "Clics : %d", PlayerClic.clicActuel);
    texteClicSurface = TTF_RenderText_Blended(police, compteurClicTexte,
                                                      couleurTextClic);

    /* Inscrit le numéro de version */

    sprintf(compteurVersionTexte, "v %d.%d.%d", versionTier_1, versionTier_2, versionTier_3);
    texteVersion = TTF_RenderText_Blended(policeVersion, compteurVersionTexte, couleurTextClic);

    /* Positionne le texte */
    positionTexteClic.x = ecran->w / 2 - texteClicSurface->w / 2;
    positionTexteClic.y = 10;

    positionTexteVersion.x = 5; /* Positionne le texte de la version en bas à gauche */
    positionTexteVersion.y = 585;

    /* Init du mob */
    mobSprite = IMG_Load("sprite/mob/mob1.png");

    mobPosition.x = ecran->w / 2 - 100 ;
    mobPosition.y = ecran->h / 2 - 100;

    /* Init du bouton shop */
    bouton_Shop = IMG_Load("sprite/shop.png");

    bouton_shopPos.x = ecran->w / 2 - bouton_Shop->w / 2;
    bouton_shopPos.y = 520;

    /** Shop Struct **/
    // Peon
    struct AutoClic Peon;
    struct Ticks PeonTick;

    Peon.qt = 0;
    Peon.stat = 0;
    Peon.tick = 0;

    /** Fichiers Shop **/
    // Peon : init
    FILE *Peon_Quantite;
    FILE *Peon_Statistique;
    FILE *Peon_Tick;

    // Peon : Openning
    // Qt
    // Stat
    Peon_Statistique = fopen("file/item/peon.st", "r");
        if(Peon_Statistique != NULL)
        {
            fscanf(Peon_Statistique, "%d", &Peon.stat);
            fclose(Peon_Statistique);
        }
            else
            {
                exit(EXIT_FAILURE);
            }
   // Ticks
    Peon_Tick = fopen("file/item/peon.time", "r");
        if(Peon_Tick != NULL)
        {
            fscanf(Peon_Tick, "%d", &Peon.tick);
            fclose(Peon_Tick);
        }
            else
            {
                exit(EXIT_FAILURE);
            }
    //


    // Timers
    PeonTick.TickPrec = 0;

    while(nonStop)
    {
        SDL_PollEvent(&jeuEvent);

        PeonTick.TickActu = SDL_GetTicks();

        /** Click auto **/
        //Peon
        if(PeonTick.TickActu - PeonTick.TickPrec > Peon.tick)
        {
            Peon_Quantite = fopen("file/item/peon.qt", "r");
            if(Peon_Quantite != NULL)
            {   
                fscanf(Peon_Quantite, "%d", &Peon.qt);
                fclose(Peon_Quantite);
            }
                else
                {
                    exit(EXIT_FAILURE);
                }
            PlayerClic.clicActuel += (Peon.qt*Peon.stat);

            /* Reset de la surface qui contenait les clics */
            SDL_FreeSurface(texteClicSurface);

            /* Inscription du nouveau montant de clic */
            sprintf(compteurClicTexte, "Clics : %d", PlayerClic.clicActuel);
            texteClicSurface = TTF_RenderText_Blended(police, compteurClicTexte,
                                                          couleurTextClic);

            PeonTick.TickPrec = PeonTick.TickActu;

        }

        /* Fermeture avec Croix */
        switch(jeuEvent.type)
        {

        case SDL_QUIT :
            exit(EXIT_SUCCESS);
            break;

            case SDL_MOUSEBUTTONDOWN : // Si le joueur enfonce le bouton de sa souris

            if(jeuEvent.button.y >= 520 && jeuEvent.button.y <= 520 + bouton_shopPos.h
               && jeuEvent.button.x > ecran->w / 2 - bouton_Shop->w / 2 
               && jeuEvent.button.x <= ecran->w / 2 - bouton_Shop->w / 2 + bouton_shopPos.w)
               // Si le joueur clic sur le bouton shop
               {
                   Shop(ecran);
                   break;
               }

            if(SDL_BUTTON_LEFT && verifClic == 0) // Si c'est le clic gauche et qu'il n'y a pas de clic actif (verifClic = 0)
            {

            PlayerClic.clicActuel++; // Clic +1

            /* Reset de la surface qui contenait les clics */
            SDL_FreeSurface(texteClicSurface);

            /* Inscription du nouveau montant de clic */
            sprintf(compteurClicTexte, "Clics : %d", PlayerClic.clicActuel);
            texteClicSurface = TTF_RenderText_Blended(police, compteurClicTexte,
                                                          couleurTextClic);

            SDL_BlitSurface(texteClicSurface, NULL, ecran, &positionTexteClic);

            verifClic = 1; // Clic effectué

            }


            break;

            case SDL_MOUSEBUTTONUP :
                if(SDL_BUTTON_LEFT)
                {
                verifClic = 0; // Si le joueur lève le bouton gauche de la souris alors clic est fait =0
                }

            break;

        default : break;

        }

        /* Fermeture avec ECHAP */
        switch(jeuEvent.key.keysym.sym)
        {
        case SDLK_s : // Presser -S appelle la fonction shop
            Shop(ecran);
            break;

        case SDLK_ESCAPE :
            nonStop = 0;
            break;

        default : break;
        }


        Sauvegarder(PlayerClic.clicActuel);

        /* Reset l'ecran */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));

        /* Blit des surfaces */
        SDL_BlitSurface(fond_jeu, NULL, ecran, &positionFondJeu);
        SDL_BlitSurface(mobSprite, NULL, ecran, &mobPosition);
        SDL_BlitSurface(bouton_Shop, NULL, ecran, &bouton_shopPos);

        /* Blit du texte */
        SDL_BlitSurface(texteClicSurface, NULL, ecran, &positionTexteClic);
        SDL_BlitSurface(texteVersion, NULL, ecran, &positionTexteVersion);

        /* Flip ecran */
        SDL_Flip(ecran);

        /* Fermeture des fichiers */


    } // Fin boucle principale
} // Fin fonction jouer()

unsigned int Sauvegarder(unsigned int ClicSave) // Sauvegarde le nombre de clics dans le fichier c_save.lrk
{
    /* Init des fichiers */
    FILE *saveClic = NULL; // Fichier sauvegarde clic
    FILE *saveItem_1 = NULL; // Fichier qui sauvegarde le nombre d'item_1

    /* Ouverture/creation des fichiers */
    saveClic = fopen("file/c_save.lrk", "w+");
        if(saveClic != NULL) // Si le fichier est ouvert correctement on inscrit les valeurs
        {
            fprintf(saveClic, "%d", ClicSave);
            fclose(saveClic);
        }
        else
        {
            exit(EXIT_FAILURE);
        }

} // Fin fonction Sauvegarder()

#endif
