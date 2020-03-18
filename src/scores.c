/**
 * \file scores.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le score
 * \brief Initialisation, mise à jour, affichage et destruction du score
 */
#include "scores.h"
#include "baseGame.h"


HUD score;


/** \fn  getScores
 *  \brief Retourne l'instance de l'objet score
 *  
 *  \return Retourne un pointeur sur l'objet score 
 *  
 *  \details Cela permet d'instaurer un contexte privée. 
 */
extern HUD* getScores()
{
   return &score;
}


// extern void Init_Scores()
// {
//     score.scoreActuel = 0;
//     score.meilleurScore = 0;
    
// }

// extern void PlayerScore(const char * text, int x,  int y)
// {
//     score.surface = TTF_RenderText_Solid(score.police, text,(SDL_Color){0, 0, 0,0});
//     score.tex = SDL_CreateTextureFromSurface( getRenderer(), score.surface );
    
//     int width, height;
//     SDL_QueryTexture(score.tex, NULL, NULL, &width, &height);

//     score.rect.x = x;
//     score.rect.y = y;
//     score.rect.w = width;
//     score.rect.h = height;
    
// }


// extern void NettoyerScore()
// {
//     if(score.tex != NULL)
//     {
//         printf("Nettoyer scores\n");
//         SDL_FreeSurface(score.surface);
//         SDL_DestroyTexture(score.tex);
//     }
    
// }

// extern void AfficherScores()
// {

//     SDL_Rect scor = {score.rect.x - camera.x  ,score.rect.y - camera.y, score.rect.w ,score.rect.h };
//     SDL_RenderCopy(getRenderer(), score.tex, NULL, &score.rect);
// }


// extern void SetScore(HUD * hud, const char * nom, int scores)
// {
//     SDL_Texture * tex = score.tex;

//     if( tex != NULL )
//     {
//         SDL_FreeSurface(score.surface);
//         SDL_DestroyTexture(score.tex);
//     }

//     char sc[30];

//     sprintf( sc, "%s : %d" , nom, scores ); 
    
//     score.surface = TTF_RenderText_Solid(score.police, sc, (SDL_Color){0, 0, 0,0});
//     score.tex = SDL_CreateTextureFromSurface( getRenderer() , score.surface );

   
//     int width, height;
//     SDL_QueryTexture(score.tex, NULL, NULL, &width, &height);

//     score.rect.w = width;
//     score.rect.h = height;
// }

// extern void nouveauScore(int nouveauScore)
// {

//     if ( nouveauScore > score.meilleurScore )
//     {
//         score.meilleurScore = nouveauScore;
//     }

//     score.scoreActuel = nouveauScore;
    
// }