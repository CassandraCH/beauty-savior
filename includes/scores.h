#ifndef _SCORES_H
#define _SCORES_H



typedef struct
{
    int meilleurScore;
    int scoreActuel;

    int numeroNiveau;

    
}Scores;


extern void Init_Scores();
extern void nouveauScore();



#endif