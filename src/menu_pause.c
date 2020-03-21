/**
 * \file menu_pause.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu de pause
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */

#include "baseGame.h"

Menu_t menu_pause; /**< Structure de type menu_t */

/**
 * \fn extern Menu_t * getMenuPause()
 * \brief Fonction qui permet retourner le menu de pause
 * \return une structure menu de type Menu_t
*/
extern Menu_t * getMenuPause()
{
    return &menu_pause;
}

/**
 * \fn extern void Init_MenuPause()
 * \brief Fonction qui initialise le menu de pause
 * \return pas de valeur de retour (void)
*/
extern void Init_MenuPause()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    ChargerData_Menu(0,0,&menu_pause , "Reprendre partie"
                ,"graphics_assets/icons_buttons/back_on_xs.png"
                ,"graphics_assets/icons_buttons/back_off_xs.png"
                ,339
                ,491 );

    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    ChargerData_Menu(1,1, &menu_pause ,"Retour menu"
                ,"graphics_assets/icons_buttons/menu_on_xs.png"
                ,"graphics_assets/icons_buttons/menu_off_xs.png"
                ,620
                ,491 );


    //Option selectionnee = Reprendre partie
    menu_pause.selectedOption = 0;

    //Chargement de la texture du menu de pause
    menu_pause.bg = ChargerTexture("graphics_assets/pause.png");
}

/**
 * \fn extern void Input_MenuPause(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_MenuPause(SDL_Event *event)
{
    // Lecture de tous les evenements
    while (SDL_PollEvent(event) != 0)
    {
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
                //Cas touche fleche de gauche
                case SDLK_LEFT:
                    Gauche(getMenuPause());
                    break;

                //Cas touche fleche de droite
                case SDLK_RIGHT:
                    Droite(getMenuPause());
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (getTouchePresse(getMenuPause()))
                    {
                        //Cas de la premiere option : reprendre la partie
                        case 0:
                            getBaseGame()->state = IN_GAME;                    
                            break;
                        //Cas de la deuxieme option : retour sur le menu principal
                        case 1:
                            actualiserJoueur();   
                            getBaseGame()->state = MENU_PRINCIPAL;       
                            return;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    } // fin while (SDL_PollEvent)
}
