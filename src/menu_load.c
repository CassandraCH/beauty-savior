/**
 * \file menu_load.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu de chargement
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */
#include "baseGame.h"

GameObject menu_load; /**< Structure de type GameObject */

/**
 * \fn extern GameObject * getMenuLoad()
 * \brief Fonction qui permet retourner le menu de chargement
 * \return une structure menu de type GameObject
*/
extern GameObject * getMenuLoad()
{
    return &menu_load;
}

/**
 * \fn extern void Load_Init()
 * \brief Fonction qui initialise le menu de chargement
 * \return pas de valeur de retour (void)
*/
extern void Load_Init()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
    //Chargement d'une partie sauvegardee
    LoadGame();

    //Creation de la texture pour le score
    SetHUD_IntToTexture(getScores(), (SDL_Color){0,0,0,0} ,"SCORES", getPlayer()->scores, 490, 245);

    //Creation de la texture pour le numero du niveau
    SetHUD_IntToTexture(getNiveau(), (SDL_Color){0,0,0,0} , "NIVEAU", getPlayer()->niveau , 490, 374 );

    menu_load.nom_gameObject = "Menu Chargement";

    /* 
     * Premiere option : Retour au menu principal
     * Actif par défaut
     */ 

    GameObject_LoadRessources(0,0,&menu_load
                ,"graphics_assets/icons_buttons/return_on_xs.png"
                ,"graphics_assets/icons_buttons/return_off_xs.png"
                ,339
                ,570 );


    /* 
     * Deuxieme option : Charger la partie
     */

    GameObject_LoadRessources(1,1, &menu_load 
                ,"graphics_assets/icons_buttons/load_on_xs.png"
                ,"graphics_assets/icons_buttons/load_off_xs.png"
                ,620
                ,570 );


    //Option selectionnee = Retour au menu principal
    menu_load.componentSelected = 0;

    //Chargement de la texture du menu de chargement
    menu_load.bg = Texture_Load("graphics_assets/chargement.png");
}

/**
 * \fn extern void Load_Input(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \brief Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Load_Input(SDL_Event *event)
{
    // Lecture de tous les evenements
    while (SDL_PollEvent(event) != 0)
    {
        //Si l'utilisateur clique sur la croix ou le bouton echap
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

        //Si une touche est appuyee
        if (event->type == SDL_KEYUP)
        {
            switch (event->key.keysym.sym)
            {
                //Cas de la fleche LEFT_Key
                case SDLK_LEFT:
                    LEFT_Key(getMenuLoad(), 2);
                    break;

                //Cas de la fleche RIGHT_Key
                case SDLK_RIGHT:
                    RIGHT_Key(getMenuLoad(), 2);
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (GetKeypressed(getMenuLoad()))
                    {
                    //Cas de la premiere option : retour au menu principal
                        case 0:
                            //Nettoyage de l'affichage
                            GameObject_Clean(getMenuLoad(), 2);
                            GameObject_Clean(getMenu_Over(), 4);

                            Player_Reset();

                            //Changer l'etat du jeu
                            getBaseGame()->state = MENU_PRINCIPAL;
                            break;

                        //Cas de la deuxieme option : charger la partie
                        case 1:
                            Level_Destroy();
                            
                            Player_Reset();

                            //Suppression des listes
                            Delete_List(getCollider());
                            Delete_List(getEnnemis());
                            Delete_List(getBullets());

                            //Changer l'etat du joueur
                            getPlayer()->estMort = false;
                            getPlayer()->nombreVies = 3;

                            //Initialisation du hud score
                            SetHUD_IntToTexture(getScores(),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "", getPlayer()->scores,560, 21);

                            //Nettoyage de l'affichage
                            GameObject_Clean(getMenu_Over(), 4);
                            GameObject_Clean(getGameObject(), 4);

                            Interface_Init();
                            //Charger le niveau
                            Level_Load();

                            //Changer l'etat du jeu
                            getBaseGame()->state = IN_GAME;

                            //Arret de la musique
                            Mix_HaltMusic();
                            return;

                            break;
                        default:
                            break;
                    }//fin du switch
                    break;
                default:
                    break;
            }//fin du switch
        }
    } // fin while (SDL_PollEvent)
}


