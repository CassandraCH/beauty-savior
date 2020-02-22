#include "scores.h"
#include "baseGame.h"

Scores score;


/** \fn  getScores
 *  \brief Retourne l'instance de l'objet score
 *  
 *  \return Retourne un pointeur sur l'objet score 
 *  
 *  \details Cela permet d'instaurer un contexte privée. 
 */
extern Scores* getScores()
{
   return &score;
}


extern void Init_Scores()
{
    score.scoreActuel = 0;
    score.meilleurScore = 0;
    
}

extern void PlayerScore(int x,  int y)
{

    // ChargerTexte(score.tex ,getMenu()->police , "Scores: 0" );
    score.surface = TTF_RenderText_Solid(score.police, "Scores: 0",(SDL_Color){0xFF, 0xFF, 0xFF, 0xFF});
    score.tex = SDL_CreateTextureFromSurface(getRenderer(), score.surface);
    
    int width, height;
    SDL_QueryTexture(score.tex, NULL, NULL, &width, &height);

    score.rect.x = x;
    score.rect.y = y;
    score.rect.w = width;
    score.rect.h = height;
    
}


extern void NettoyerScore()
{
    SDL_FreeSurface(score.surface);
    SDL_DestroyTexture(score.tex);  
}

extern void DessinerScores()
{
    SDL_RenderCopy(getRenderer(), score.tex, NULL, &score.rect);
}


extern void SetScore(int scores)
{
    SDL_Texture * tex = score.tex;

    if( tex != NULL )
    {
        SDL_FreeSurface(score.surface);
        SDL_DestroyTexture(score.tex);
    }

    char sc[20];
    sprintf( sc, "Scores: %d" , scores ); 

    int width, height;
    SDL_QueryTexture(score.tex, NULL, NULL, &width, &height);

    score.rect.w = width;
    score.rect.h = height;
}

extern void nouveauScore(int nouveauScore)
{

    if ( nouveauScore > score.meilleurScore )
    {
        score.meilleurScore = nouveauScore;
    }

    score.scoreActuel = nouveauScore;
    
}