/**
 * \file menuLoad.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu de chargement
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */
#include "baseGame.h"

Menu_t menu_load; /**< Structure de type menu_t */

/**
 * \fn extern Menu_t * getMenuLoad()
 * \brief Fonction qui permet retourner le menu de chargement
 * \return une structure menu de type Menu_t
*/
extern Menu_t * getMenuLoad()
{
    return &menu_load;
}

/**
 * \fn extern void Init_MenuLoad()
 * \brief Fonction qui initialise le menu de chargement
 * \return pas de valeur de retour (void)
*/
extern void Init_MenuLoad()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
    //Chargement d'une partie sauvegardee
    ChargerPartie();

    //Creation de la texture pour le score
    SetHUD_IntToTexture(getScores(), "SCORES", getPlayer()->nb_objet, 490, 245);

    //Creation de la texture pour le numero du niveau
    SetHUD_IntToTexture(getNiveau(), "NIVEAU", getPlayer()->niveau , 490, 374 );

    /* 
     * Premiere option : Retour au menu principal
     * Actif par défaut
     */ 

    ChargerData_Menu(0,0,&menu_load , "Retour"
                ,"graphics_assets/icons_buttons/return_on_xs.png"
                ,"graphics_assets/icons_buttons/return_off_xs.png"
                ,339
                ,570 );


    /* 
     * Deuxieme option : Charger la partie
     */

    ChargerData_Menu(1,1, &menu_load ,"Charger Partie"
                ,"graphics_assets/icons_buttons/load_on_xs.png"
                ,"graphics_assets/icons_buttons/load_off_xs.png"
                ,620
                ,570 );


    //Option selectionnee = Retour au menu principal
    menu_load.selectedOption = 0;

    //Chargement de la texture du menu de chargement
    menu_load.bg = ChargerTexture("graphics_assets/chargement.png");
}

/**
 * \fn extern void Input_MenuLoad(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_MenuLoad(SDL_Event *event)
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
                //Cas de la fleche gauche
                case SDLK_LEFT:
                    Gauche(getMenuLoad(), 2);
                    break;

                //Cas de la fleche droite
                case SDLK_RIGHT:
                    Droite(getMenuLoad(), 2);
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (getTouchePresse(getMenuLoad()))
                    {
                    //Cas de la premiere option : retour au menu principal
                        case 0:
                            //Nettoyage de l'affichage
                            Nettoyer_Menu(getMenuLoad(), 2);
                            Nettoyer_Menu(getMenu_Over(), 4);

                            actualiserJoueur();

                            //Changer l'etat du jeu
                            getBaseGame()->state = MENU_PRINCIPAL;
                            break;

                        //Cas de la deuxieme option : charger la partie
                        case 1:
                            DestructionNiveau();
                            actualiserJoueur();

                            //Changer l'etat du joueur
                            getPlayer()->estMort = false;

                            //Initialisation du hud score
                            SetHUD_IntToTexture(getScores(), "SCORES", getPlayer()->nb_objet, 10, 0);

                            //Nettoyage de l'affichage
                            Nettoyer_Menu(getMenu(), 4);
                            
                            //Charger le niveau
                            ChargerNiveau();

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


