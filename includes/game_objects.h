/**
 * \file game_objects.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gère les objets
 */



#ifndef _GAME_OBJECTS_H
/*! \def _GAME_OBJECTS_H */
#define _GAME_OBJECTS_H


#include "texture.h"

/** @brief  Nombre maximum d'options disponibles dans un menu */
#define MAX_NUMBER 3 


/**
 *\struct component
 *\brief Structure gérant les caractéristiques liées à un component
 * \details  Les components sont toujours liés à un gameObject,ils définissent le comportement de ce GameObject. 
 */
typedef struct component
{
    int largeur;            /**< la largeur de l'option */
    int hauteur;            /**< la hauteur de l'option */
    const char * nomOption; /**< le nom de l'option */
    SDL_Texture *texture;   /**< le texture de l'option */
    int x;                  /**< la position en x de l'option   */
    int y;                  /**< la position en y de l'option   */
    char * filename[4];     /**<le fichiers contenant la texture de l'option */

}Component;
/**< Typedef component Component */


/**
 *\struct gameObject
 *\brief Structure permettant de gérer un GameObject
 *\details Le GameObject représente une boîte vide qui ne fait pas grand chose tout seul, il agit comme un conteneur pour les components.
 */
struct gameObject
{
    int componentSelected;              /**< Component selectionne  */
    Component components[4];            /**< Tableau de Components  */
    Mix_Chunk *son;                     /**< Le son du gameObject   */
    TTF_Font * police;                  /**< La police utilise pour le gameObject */
    SDL_Texture * bg;                   /**< Texture en arrière-plan */
    Mix_Music * bgm;                    /**< Musique du jeux en arriere plan*/
    char * nom_gameObject;              /**< Nom du GameObject  */

} GameObject;
/**< Typedef gameObject GameObject */

extern void UpdateComponent(Component * component, int etat);                       /**< fonction de mise à jour du component d'un gameObject */
extern void UpdateImage_Component(Component * component, const char * filename);    /**< fonction de mise à jour d'image du component d'un gameObject*/

extern int  GetKeypressed( GameObject *gameObject );                                /**< fonction sur les touches du gameObject*/
extern void GameObject_LoadRessources(int numero,int num_image, GameObject * gameObject,  char * nomOption,  char * image_on,  char * image_off,
                int positionX, int positionY );                                     /**< rechargement du gameObject */


extern void UP_Key(GameObject * gameObject);                                        /**< fonction pour la touche haut du gameObject */
extern void DOWN_Key(GameObject *gameObject );                                      /**<touche bas  */

extern void RIGHT_Key(GameObject *gameObject, int nombreOptions);                       /**< pour aller a Droite */
extern void LEFT_Key(GameObject *gameObject,int nombreOptions);                         /**< pour aller a Gauche */

extern void GameObject_Render(GameObject* gameObject, int nombresOptions, int posX, int posY , int largeurBG, int hauteurBG); /* Rendu d'un gameObject */
extern void GameObject_Clean(GameObject * gameObject, int nombreOptions);           /**< fonction servant à libérer les ressources d'un gameObject */


#endif