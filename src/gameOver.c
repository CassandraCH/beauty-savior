/**
 * \file gameover.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu du game over
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */

#include "baseGame.h"

GameObject menu_over; /**< Structure de type GameObject */

/**
 * \fn extern GameObject * getMenu_Over()
 * \brief Fonction qui permet de retourner le menu du game over
 * \return une structure menu de type GameObject
*/
extern GameObject * getMenu_Over()
{
    return &menu_over;
}

/**
 * \fn extern void GameOver_Init()
 * \brief Fonction qui initialise le menu game over
 * \return pas de valeur de retour (void)
*/
extern void GameOver_Init()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Game Over");
    
   

    //chargement du son
    menu_over.son = Mix_LoadWAV("sounds/menu_click.wav");
    menu_over.bgm = Mix_LoadMUS("sounds/awesomeness.wav");

    /* 
     * Première option : demarer une nouvelle partie 
     * Actif par défaut
     */
    GameObject_LoadRessources(0, 0, &menu_over, "Nouvelle partie", "graphics_assets/icons_buttons/newpartie_on_xs.png", "graphics_assets/icons_buttons/newpartie_off_xs.png", 469, 366);

    /* 
     * Deuxième option : Chargement d'une partie
     */
    GameObject_LoadRessources(1, 1, &menu_over, "Chargement", "graphics_assets/icons_buttons/load_on_xs.png", "graphics_assets/icons_buttons/load_off_xs.png", 455, 449);
    
    /* 
     * Troisième option : quitter le jeu 
     */
    GameObject_LoadRessources(2, 1, &menu_over, "Quitter", "graphics_assets/icons_buttons/quitter_on_xs.png", "graphics_assets/icons_buttons/quitter_off_xs.png", 469, 491);

    /* 
     * Quatrième option : Couper/Activer Son
     */
    GameObject_LoadRessources(3, 1, &menu_over, "Son", "graphics_assets/icons_buttons/sound_on_xs.png", "graphics_assets/icons_buttons/sound_off_xs.png", 487, 627);
    
    
    //Option selectionnée par défaut = la première (nouvelle partie)
    menu_over.componentSelected = 0;

    //Chargement de la texture du menu game over
    menu_over.bg = Texture_Load("graphics_assets/menu_over_bg.png");
}

/**
 * \fn extern void GameOver_Input(SDL_Event *event)
 * \brief Fonction qui gère les évènements du menu
 * \brief Gestion des entrées clavier de l'utilisateur
 * \param event évènement
 * \return pas de valeur de retour (void)
*/
extern void GameOver_Input(SDL_Event *event)
{
    // Lecture de tous les évènements
    while (SDL_PollEvent(event) != 0)
    {
        //Si l'utilisateur clique sur la croix ou le bouton echap
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

        //Si une touche est appuyée
        if (event->type == SDL_KEYUP)
        {
            switch (event->key.keysym.sym)
            {
                //Cas de la touche flèche du haut
                case SDLK_UP:
                    //Gestion du son
                    Mix_PlayChannel(-1, getGameObject()->son, 0);
                    //Navigation dans le menu
                    UP_Key(getMenu_Over());
                    break;

                //Cas de la touche flèche du bas
                case SDLK_DOWN:
                    //Gestion du son
                    Mix_PlayChannel(-1, getGameObject()->son, 0);
                    //Navigation dans le menu
                    DOWN_Key(getMenu_Over());
                    break;

                //Cas de la touche entrée
                case SDLK_RETURN:
                    switch (GetKeypressed(getMenu_Over()))
                    {
                        //Cas de la première option : nouvelle partie
                        case 0:
                            printf("Nouvelle partie depuis gameover");

                            //Nettoyage de l'affichage
                            GameObject_Clean(getMenu_Over(), 4);
                            GameObject_Clean( getGameObject() , 4);

                            //Changement de l'état du joueur
                            getPlayer()->estMort = false;
                            getPlayer()->nombreVies = 3;

                            //Chargement du hud avec 3 vies
                            UpdateImage_Component( &getInterface()->components[2] , "graphics_assets/vie_3.png" );

                            //Suppression des listes
                            Delete_List(getCollider());
                            Delete_List(getEnnemis());
                            Delete_List(getBullets());

                            Player_Reset();

                            //Initialisation du hud score
                            Init_HUD(getScores(),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "0", 565, 17);

                            //Changement de l'état du jeu
                            getBaseGame()->state = IN_GAME;

                            //Charger le niveau
                            Level_Load();

                            Mix_HaltMusic();
                            return;
                            break;

                        //Cas de la deuxièmme option : chargement d'une partie
                        case 1:
                            printf("Chargement depuis gameover");

                            //Nettoyage de l'affichage
                            GameObject_Clean(getMenu_Over(), 4);
                            GameObject_Clean( getGameObject() , 4);

                            Load_Init();
                            GameObject_Clean(getGameObject(), 4);

                            //Changement de l'état du jeu
                            getBaseGame()->state = LOADING;

                            //Arrêt de la musique
                            Mix_HaltMusic();
                            break;

                        //Cas de la troisième option : quitter
                        case 2:
                            //Changement de l'état du jeu
                            getBaseGame()->estActif = false;
                            return;
                            break;

                        default:
                            break;
                    }//fin switch
                    break;

                //Cas de la touche s
                case SDLK_s:
                    //Si la musique est en pause
                    if (Mix_PausedMusic() == 1)
                    {
                        //Rafraîchir l'affichage
                        UpdateComponent(&menu_over.components[3], 0);
                        //On enlève la pause (la musique repart où elle en était)
                        Mix_ResumeMusic();
                    }

                    //Si la musique est en train de jouer
                    else
                    {
                        //Rafraîchir l'affichage
                        UpdateComponent(&menu_over.components[3], 1);
                        //On met en pause la musique
                        Mix_PauseMusic();
                    }
                    break;
                    
                default:
                    break;
            }//fin switch
        }
    } // fin while (SDL_PollEvent)
}

/**
 * \fn extern void GameOver_Load()
 * \brief Fonction qui initialise l'état game over
 * \return pas de valeur de retour (void)
*/
extern void GameOver_Load()
{
    //Changement de l'etat du joueur et remise à 0 du score
    getPlayer()->estMort = true;
    getPlayer()->scores = 0;
    getPlayer()->isPasspordCollected = false;
    UpdateComponent( &getInterface()->components[4], 1);

    //Rechargement du niveau 1
    Set_Level(1);
    setOs(0);
    setBranche(0);
    setRock(0);

    GameObject_Clean(getGameObject(), 4);
    GameOver_Init();

    //Suppression des listes
    Delete_List( getCollider() );
    Delete_List(getEnnemis());
    Delete_List(getBullets());

    //Detruire les niveau
    Level_Destroy();

    //Changement de l'etat du jeu = game over
    getBaseGame()->state = GAMEOVER;

    //Gestion du temps
    getBaseGame()->time = 0;
    getBaseGame()->tempsActuel = 0;
    getBaseGame()->tempsPrecedent = 0;
    getBaseGame()->min = 60;
}
