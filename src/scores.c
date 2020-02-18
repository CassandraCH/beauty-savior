#include "scores.h"

Score score;



extern void Init_Scores()
{
    score.numeroNiveau = 0;
    score.meilleurScore = 0;
    score.numeroNiveau = 0;
}

/** \fn  getScores
 *  \brief Retourne l'instance de l'objet score
 *  
 *  \return Retourne un pointeur sur l'objet score 
 *  
 *  \details Cela permet d'instaurer un contexte privée. 
 */
extern Score* getScores()
{
   return &score;
}




extern void nouveauScore(int nouveauScore)
{
;
    if ( nouveauScore > score.meilleurScore )
    {
        score.meilleurScore = nouveauScore;
    }

    score.scoreActuel = nouveauScore;
    
}