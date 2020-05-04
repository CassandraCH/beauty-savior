/**
 * \file menu_continue.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu "continuer", lorsqu'un niveau vient d'etre termine
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */
#include "baseGame.h"

GameObject menu_continue; /**< Structure de type GameObject */

/**
 * \fn extern GameObject * getMenuCon()
 * \brief Fonction qui permet retourner le menu "continuer"
 * \return une structure menu de type GameObject
*/
extern GameObject * getMenuCon()
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

    SetHUD_IntToTexture(getScores(),(SDL_Color){0,0,0,0}, "SCORES", getPlayer()->scores, 490, 245);
   
    SetHUD_IntToTexture(getNiveau(),(SDL_Color){0,0,0,0}, "NIVEAU", getPlayer()->niveau , 510, 374);

    menu_continue.nom_gameObject = "Menu Continue";
    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */
    GameObject_LoadRessources(0, 0, &menu_continue, "Continuer", "graphics_assets/icons_buttons/continue.png", "null", 707, 562);

    //Option selectionnee = Reprendre partie
    menu_continue.componentSelected = 0;

    //Chargement de la texture du menu "continuer"
    menu_continue.bg = Texture_Load("graphics_assets/levelComplete.png");
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
                    switch (GetKeypressed(getMenuCon()))
                    {
                        //Premiere option selectionnee
                        case 0:
                            //Changer l'etat du jeu
                            getBaseGame()->state = IN_GAME;
                            Set_Level( ++getPlayer()->niveau) ;

                            //Sauvegarder la partie
                            SauvegarderPartie();

                            //Suppression des listes
                            Delete_List(getCollider());
                            Delete_List(getEnnemis());
                            Delete_List(getBullets());

                            //Initialisation du hud score avec le nombre de points du niveau précédent
                            SetHUD_IntToTexture( getScores(),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "", getPlayer()->scores,560, 21   );
                          

                            getBaseGame()->tempsActuel = 0;
                            getBaseGame()->tempsPrecedent = 0;
                            getBaseGame()->min = 60;
                          
                        
                            //Position initiale du joueur 
                            getPlayer()->x = 100;
                            getPlayer()->y = 50;

                            //le passport est remis en non collecté
                            getPlayer()->isPasspordCollected = false;
                            UpdateComponent( &getInterface()->components[4], 1);

                        
                            //Charger le niveau next
                            Level_Load();  
                              
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
 * \brief Fonction qui initialise l'etat continue
 * \details 
 * \return pas de valeur de retour (void)
*/
extern void Init_Continue()
{
   // NettoyerScore();
    Level_Destroy();

    //Initialisation du hud de score
    Init_HUD(getNiveau(),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "NIVEAU : 0", 530, 374);

    //Initialisation du menu "continuer"
    Init_MenuContinue();
    
    //Changement de l'etat du jeu
    getBaseGame()->state = LEVEL_COMPLETED;

    getBaseGame()->time = 0;
   
}