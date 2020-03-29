/**
 * \file hud.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme gere l'affichage des informations concernant le joueur notamment le score, le nombre de vie etc.
 */



#ifndef HUD_H
#define HUD_H/**< \def HUD_H*/

/**
* \struct hud_s
* \details structure gerant les informations concernant le joueur
*/
typedef struct hud_s
{
    TTF_Font* police;/**<la police qui est utilise pour l'affichage du hud*/
	SDL_Surface* surface;/**<la surface qui sera convertit en texture*/
    SDL_Texture *tex;/**< correspond a la texture du hud,c'est a dire ce qui sera affiché*/
	SDL_Rect rect;/**< le rectangle ou sera afficher le rendu du hud*/

}HUD;
/**< This is the documentation for the preceding typedef */


extern void Init_HUD(HUD * hud, const char * text, int x,  int y);/**<initialisation de hud*/
extern void NettoyerHUD(HUD * hud);/**< nettoyer, renitialliser le hud*/
extern void SetHUD_IntToTexture(HUD * hud, const char * nom, int scores, int posX, int posY);
extern void AfficherHUD(HUD * hud);/**< l'affichage de hud*/



#endif
