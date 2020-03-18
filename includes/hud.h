#ifndef HUD_H
#define HUD_H

typedef struct hud_s
{
    TTF_Font* police;
	SDL_Surface* surface;
    SDL_Texture *tex;
	SDL_Rect rect;

}HUD;



extern void Init_HUD(HUD * hud, const char * text, int x,  int y);
extern void NettoyerHUD(HUD * hud);
extern void SetHUD_IntToTexture(HUD * hud, const char * nom, int valeur);
extern void AfficherScores(HUD * hud);


#endif