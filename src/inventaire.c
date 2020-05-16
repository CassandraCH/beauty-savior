/**
 * \file inventaire.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date avril 2020
 * \brief Programme qui gère l'inventaire (liste des objets collectés par le joueur) 
 */
#include "basegame.h"

GameObject inventaire; /**< Structure de type GameObject */

int nombreOs = 0; /**< Compteur du nombre d'os*/
int nombreRock = 0; /**< Compteur du nombre de cailloux*/
int nombreBranche = 0; /**< Compteur du nombre de branches*/

/**
 * \fn extern GameObject* getInventaire()
 * \brief Fonction qui permet de retourner l'interface 
 * \return un pointeur sur l'interface
*/
extern GameObject* getInventaire()
{
    return &inventaire;
}

/**
 * \fn extern int getOs()
 * \brief Fonction qui permet de retourner le nombre d'os
 * \return le compteur d'os
*/
extern int getOs()
{ 
    return nombreOs; 
}

/**
 * \fn extern int getRock()
 * \brief Fonction qui permet de retourner le nombre de cailloux
 * \return le compteur de cailloux
*/
extern int getRock()
{
    return nombreRock; 
}

/**
 * \fn extern int getBranche()
 * \brief Fonction qui permet de retourner le nombre de branches
 * \return le compteur de branches
*/
extern int getBranche()
{ 
    return nombreBranche;
}

/**
 * \fn extern void setOs(int value)
 * \param value valeur à appliquer au compteur
 * \brief Fonction qui permet d'initialiser le compteur d'os
 * \return pas de valeur de retour (void)
*/
extern void setOs(int value)
{ 
    nombreOs = value; 
}

/**
 * \fn extern void setRock(int value)
 * \param value valeur à appliquer au compteur
 * \brief Fonction qui permet d'initialiser le compteur de cailloux
 * \return pas de valeur de retour (void)
*/
extern void setRock(int value)
{ 
    nombreRock= value;  
}

/**
 * \fn extern void setBranche(int value)
 * \param value valeur à appliquer au compteur
 * \brief Fonction qui permet d'initialiser le compteur de branches
 * \return pas de valeur de retour (void)
*/
extern void setBranche(int value)
{ 
    nombreBranche= value;  
}

/**
 * \fn extern void increaseOs()
 * \brief Fonction qui permet d'incrémenter le compteur d'os
 * \return pas de valeur de retour (void)
*/
extern void increaseOs()
{
    ++nombreOs; 
}

/**
 * \fn extern void increaseRock()
 * \brief Fonction qui permet d'incrémenter le compteur de cailloux
 * \return pas de valeur de retour (void)
*/
extern void increaseRock()
{
    ++nombreRock; 
}

/**
 * \fn extern void increaseBranche()
 * \brief Fonction qui permet d'incrémenter le compteur de branches
 * \return pas de valeur de retour (void)
*/
extern void increaseBranche()
{
    ++nombreBranche; 
}

/**
 * \fn extern void decreaseOS()
 * \brief Fonction qui permet de décrémenter le compteur d'os
 * \return pas de valeur de retour (void)
*/
extern void decreaseOS()
{ 
    --nombreOs; 
}

/**
 * \fn extern void decreaseRock()
 * \brief Fonction qui permet de décrémenter le compteur de cailloux
 * \return pas de valeur de retour (void)
*/
extern void decreaseRock()
{
    --nombreRock; 
}

/**
 * \fn extern void decreaseBranche()
 * \brief Fonction qui permet de décrémenter le compteur de branches
 * \return pas de valeur de retour (void)
*/
extern void decreaseBranche()
{
    --nombreBranche; 
}

/**
 * \fn extern void Inventaire_Init()
 * \brief Fonction qui initialise l'inventaire
 * \return pas de valeur de retour (void)
*/
extern void Inventaire_Init()
{  
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Inventaire");

    SetHUD_IntToTexture(getItem(0),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "", nombreOs, 595, 347);
    SetHUD_IntToTexture(getItem(1),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "", nombreRock , 720, 347);
    SetHUD_IntToTexture(getItem(2),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "", nombreBranche ,835, 347);

    //Première option : Sélectionner les os
    GameObject_LoadRessources(0,0, &inventaire 
                ,"graphics_assets/inventaire/os_on.png"
                ,"graphics_assets/inventaire/os_off.png"
                ,555
                ,300 );

    //Deuxième option : Sélectionner les cailloux
    GameObject_LoadRessources(1,1, &inventaire 
                ,"graphics_assets/inventaire/rock_on.png"
                ,"graphics_assets/inventaire/rock_off.png"
                ,675
                ,310 );

    //Troisième option : Sélectionner les branches
    GameObject_LoadRessources(2,1, &inventaire 
                ,"graphics_assets/inventaire/tree_on.png"
                ,"graphics_assets/inventaire/tree_off.png"
                ,790
                ,300 );


    //Option selectionnee = Sélectionner les os
    inventaire.componentSelected = 0;

    //Chargement de la texture de l'inventaire
    inventaire.bg = Texture_Load("graphics_assets/inventaire/bg_inventaire.png");
}

/**
 * \fn extern void Inventaire_Input(SDL_Event *event)
 * \brief Fonction qui gère les évènements de l'inventaire
 * \brief Gestion des entrées clavier de l'utilisateur
 * \param event évènement
 * \return pas de valeur de retour (void)
*/
extern void Inventaire_Input(SDL_Event *event)
{
    // Lecture de tous les evenements
    while (SDL_PollEvent(event) != 0)
    {
        //Cas où l'utilsateur appuie sur la croix ou sur la touche echap
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            //changer l'état du jeu
            getBaseGame()->isActive = false;
            return;
        }

        //Si une touche est appuyee
        if (event->type == SDL_KEYUP)
        {
            switch (event->key.keysym.sym)
            {
                //Cas touche flèche de LEFT_Key
                case SDLK_LEFT:
                    LEFT_Key(getInventaire(), 3);
                    break;

                //Cas touche flèche de RIGHT_Key
                case SDLK_RIGHT:
                    RIGHT_Key(getInventaire(), 3);
                    break;

                //Cas de la touche entrée
                case SDLK_RETURN:
                    switch (GetKeypressed(getInventaire()))
                    {
                        //Cas 1 : on sélectionne l'os comme objet
                        case 0:
                            //Si le joueur a récolté au moins 1 vie
                            if( getOs() > 0 )
                            {
                                //Ajouter un point de vie
                                getPlayer()->nombreVies++;
                                
                                //Mise à jour du compteur d'os
                                decreaseOS();
                                
                                //Gestion de l'affichage => mise à jour
                                switch( getPlayer()->nombreVies )
                                {
                                    case 1: UpdateImage_Component( &getInterface()->components[2], "graphics_assets/vie_1.png" ); break;
                                    case 2: UpdateImage_Component( &getInterface()->components[2], "graphics_assets/vie_2.png" ); break;
                                    case 3: UpdateImage_Component( &getInterface()->components[2], "graphics_assets/vie_3.png" ); break;
                                }
                                printf("Il reste %d points de vie\n", getPlayer()->nombreVies );
                            }
                            //changer l'état du jeu
                            getBaseGame()->state = IN_GAME;                    
                            break;

                        //Cas 2 : on sélectionne le rocher comme objet
                        case 1:
                            //Si le joueur a récolté au moins 1 caillou
                            if (getRock() > 0)
                            {
                                getPlayer()->osActif = false;  
                                getPlayer()->rockActif = true;  
                                getPlayer()->treeActif = false;

                                //Gestion de l'affichage => mise à jour
                                UpdateImage_Component( &getInterface()->components[1], "graphics_assets/items2.png" );
                            }
                            getBaseGame()->state = IN_GAME;        
                            break;

                        //Cas 3 : on sélectionne la branche comme objet    
                        case 2:
                            //Si le joueur a récolté au moins 1 branche
                            if( getBranche() > 0 )
                            {
                                getPlayer()->osActif = false;  
                                getPlayer()->rockActif = false;  
                                getPlayer()->treeActif = true;

                                //Gestion de l'affichage => mise à jour
                                UpdateImage_Component( &getInterface()->components[1], "graphics_assets/items1.png" );
                            }
                            getBaseGame()->state = IN_GAME;        
                            break;
                
                    }//fin du switch
                    break;
                default:
                    break;
                } //fin du switch
        }
    } // fin while (SDL_PollEvent)
}

