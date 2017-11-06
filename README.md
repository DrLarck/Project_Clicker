# Project_Clicker
[WIP] My first Clicker game

Descriptif de l'application :

 Jeu de type Clicker, où le joueur sera amenné à cliquer frénétiquement sur sa souris pour faire monter son nombre de points. Plus le joueur aura de points, plus les améliorations qu'il débloquera seront efficaces (Augmentation du nombre de click, cliqueur automatique, etc ...).
 
But du jeu : 

À définir, mais ce sera quelque chose du genre : Réussir à faire X click en peu de temps (réalisable qu'avec un certain nombre d'améliorations débloquées au préalable par le joueur).

Technique :

Le programme comportera plusieurs fichiers. Il devra être capable de lire dans les fichiers et d'y écrire. Ce sera une application SDL rédigée en SDL_1 (+ SDL_Image, SDL_Ttf).
Chaque fichier représentera une amélioration (Hors fichiers jeu, et permettant le fonctionnement de l'application).
La fonction main aura pour role de : Afficher le menu du jeu (Bouton Jouer - Quitter). Le bouton jouer appellera la fonction "jouer" qui aura pour but de lancer le jeu : Cette fonction affichera une image au centre de l'écran, un menu sur le bas de l'écran (Bouton : Shop/Boss/Save/Quit) cliquable. Ce sera la fonction qui aura pour but d'enregistrer le nombre de clic fait par le joueur et de mettre en action les différentes améliorations débloquées par ce dernier (notamment grâce à une série de fopen qui permettront de déterminer les améliorations possédées par le joueur).

En haut de l'écran de jeu seront affichées différentes informations :

Le nombre de clics TOTAL, le nombre de clic auto du joueur (par seconde).
