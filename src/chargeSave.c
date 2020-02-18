#include "load_save.h"
#include <stdlib.h>
#include <stdio.h>

extern void LoadGame()
{
    FILE * file = fopen("data.txt", "r");


    if (file == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);    
    }

    if( fscanf(file,"%f %f", &getPlayer()->x, &getPlayer()->y) )
    {
        printf( "Score charger: %f-%f\n", getPlayer()->x, getPlayer()->y);
        fclose(file);

    }
    
}

extern void SaveGame()
{
    FILE * file = fopen("data.txt", "a");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }

    fprintf(file,"%f %f", getPlayer()->x , getPlayer()->y );
    
    fclose(file);
}

extern void SaveNode_Position(LinkedList * lst)
{
    FILE * file = fopen("niveau1.txt", "w");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    Node * pt;
    
    if( lst->nodeCount  > 0 )
    {
        for( pt = lst->head; pt != NULL; pt = pt->next )
        {
             fprintf(file,"%d %d\n", pt->rect->x , pt->rect->y );
        }
    }

    fclose(file);
}

extern void ChargementCollider(const char * filename) 
{
    FILE * file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    Node * pt;
    
    if( Listes()->nodeCount  > 0 )
    {
        for( pt = Listes()->head; pt != NULL; pt = pt->next )
        {
            if (fscanf(file, "%d %d",&pt->rect->x , &pt->rect->y) )
            {

            }
        }
    }

    fclose(file);
}

extern void Chargement_CreationPNJ(const char * filename)
{
    FILE * file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    int typeCollider;
    int isLeft;

    while( !feof(file) )
    {
        SDL_Rect *rect = malloc( sizeof(SDL_Rect));       
        if( fscanf(file, "%d %d %d %d %d %d",&typeCollider,&isLeft,  &rect->x , &rect->y, &rect->w, &rect->h) )
        {
            insertQueue(Listes(), rect, typeCollider, isLeft);
        }
    }
	
    fclose(file);
}

extern void ChargementEnnemis(const char * filename) 
{
    FILE * file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    
   
    while( !feof(file) )
    {
        SDL_Rect *rect = malloc( sizeof(SDL_Rect));
        rect->w = 50;
        rect->h = 50;             
        if( fscanf(file, "%d %d",&rect->x , &rect->y) ){
            insertQueue(listEnnemies,  rect, ennemy, false );
        }
    }

    fclose(file);
}
