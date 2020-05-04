/**
 * \file inventaire.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief fichier qui gere l'inventaire durant le jeu
 */




#ifndef _INVENTAIRE_H
#define _INVENTAIRE_H /**< \def _MENU_CONTINUE_H*/



extern void Inventaire_Init();                  /**< l'initialisation du menu continue  */
extern void Inventaire_Input(SDL_Event *event); /**< fonction input pour le menu continue   */

extern void setOs(int value);                   /**< l'initialisation du compteur d'os  */
extern void setRock(int value);                 /**< l'initialisation du compteur de cailloux  */
extern void setBranche(int value);              /**< l'initialisation du compteur de branches */

extern void increaseOs();                       /**< incrémentation du compteur d'os  */
extern void increaseRock();                     /**< incrémentation du compteur de cailloux  */
extern void increaseBranche();                  /**< incrémentation du compteur de branches */

extern void decreaseOS();                       /**< décrémentation du compteur d'os  */
extern void decreaseRock();                     /**< décrémentation du compteur de cailloux  */
extern void decreaseBranche();                  /**< décrémentation du compteur de branches  */




#endif
