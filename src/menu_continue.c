/**
 * \file menu_continue.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu "continuer", lorsqu'un niveau vient d'etre termine
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */
#include "baseGame.h"

Menu_t menu_continue; /**< Structure de type Menu_t */

/**
 * \fn extern Menu_t * getMenuCon()
 * \brief Fonction qui permet de retourner le menu "continuer"
 * \return une structure menu de type Menu_t
*/
extern Menu_t * getMenuCon()
{
    return &menu_continue;
}

/**
 * \fn extern void Init_MenuContinue()
 * \brief Fonction qui initialise le menu "continuer"
 * \return pas de valeur de retour (void)
*/
extern void Init_MenuContinue()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Continue");

    //Creation de la texture pour le score
    SetHUD_IntToTexture(getScores(), "SCORES", getPlayer()->nb_objet, 530, 245);

    //Creation de la texture pour l'affichage du numero du niveau
    SetHUD_IntToTexture(getNiveau(), "NIVEAU", getPlayer()->niveau , 535, 374);

    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */
    ChargerData_Menu(0, 0, &menu_continue, "Continuer", "graphics_assets/icons_buttons/continue.png", "null", 707, 562);

    //Option selectionnee = Reprendre partie
    menu_continue.selectedOption = 0;

    //Chargement de la texture du menu "continuer"
    menu_continue.bg = ChargerTexture("graphics_assets/levelComplete.png");
}

/**
 * \fn extern void Input_MenuContinue(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_MenuContinue(SDL_Event *event)
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
                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (getTouchePresse(getMenuCon()))
                    {
                        //Premiere option selectionnee
                        case 0:
                            //Changer l'etat du jeu
                            getBaseGame()->state = IN_GAME;
                            setNiveau(2);

                            //Sauvegarder la partie
                            SauvegarderPartie();

                            //Suppression des listes
                            suppListe(getCollider());
                            suppListe(getEnnemis());
                            suppListe(getBullets());

                            //Initialisation du hud score
                            Init_HUD(getScores(), "SCORES : 0", 10, 0);

                            //Position initiale du joueur 
                            getPlayer()->x = 86;
                            getPlayer()->y = 495;

                            //Charger le niveau suivant
                            ChargerNiveau();       
                            break;
                        default:
                            break;
                    }//fin du switch
                    break;
                default:
                    break;
            } //fin du switch
        }
    } // fin while (SDL_PollEvent)
}

/**
 * \fn extern void Init_Continue()
 * \brief Fonction qui initialise l'etat "continue"
 * \details 
 * \return pas de valeur de retour (void)
*/
extern void Init_Continue()
{
    // NettoyerScore();
    // DestructionNiveau();

    //Initialisation du hud de score
    Init_HUD(getNiveau(), "NIVEAU : 0", 530, 374);

    //Initialisation du menu "continuer"
    Init_MenuContinue();
    
    //Changement de l'etat du jeu
    getBaseGame()->state = LEVEL_COMPLETED;

    getBaseGame()->time = 0;
    setTimerBullet(0);
}