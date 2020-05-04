/**
 * \file level.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le debut de mises en place du passage des niveaux .
 */



#ifndef __LEVEL_H
#define __LEVEL_H /**< \def __LEVEL_H*/

#include "texture.h"
/**
* \struct level
* \brief structure gerant les niveux
*/
typedef struct level
{

    Texture_Manager levelTextures[5];   /**< levelTextures */
    Texture_Manager layer_1;            /**<la couche 1  */
    Texture_Manager layer_2;            /**<la couche 2  */
    Texture_Manager layer_3;            /**<la couche 3  */

    int departX;    /**<Position de depart du joueur dans le niveau en X    */
    int departY;    /**<Position de depart du joueur dans le niveau en Y    */

    int cameraX;    /**< le position x de la camera */
    int cameraY;    /**< la position y de la camera */


}Level;
/**< This is the documentation for the preceding typedef */


extern Level *  Get_Level();                                /**< le niveau  */
extern void     Set_Level(int niveau);                      /**< le niveau correspond   */
extern void     Level_Load();                               /**< le chargemnts des niveaux  */
extern void     Level_Render();                             /**< l'affichage des niveaux    */
extern void     Level_Destroy();                            /**< les destruction des niveaux    */

extern void     Level_Textures_Render(int niveau);          /**<l'affichage des textures des niveaux    */
extern void     Debug_AfficherCollider();                   /**< le Debug_AfficherCollider  */

#endif
