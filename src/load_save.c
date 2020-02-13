#include "load_save.h"
#include <stdlib.h>
#include <stdio.h>


/*
*   C
*/
extern void ChargerPartie()
{
    FILE * file = fopen("data.txt", "r");


    if (file == NULL) {
        fprintf(stderr, "Impossibilité de charger le fichier!\n");
        exit(1);    
    }

    fclose(file);
    
}

extern void SauvegarderPartie()
{
    FILE * file = fopen("data.txt", "a");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }

    
    fclose(file);
}

extern void SauvegarderPos_Noeud(LinkedList * lstptr)
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
            fscanf(file, "%d %d",&pt->rect->x , &pt->rect->y);
        }
    }

    fclose(file);
}

extern void Chargement_CreationPNJ(const char * filename, typeItem type )
{
    FILE * file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }

    while( !feof(file) )
    {
        SDL_Rect *rect = malloc( sizeof(SDL_Rect));       
        fscanf(file, "%d %d %d %d",&rect->x , &rect->y, &rect->w, &rect->h);
        insertQueue(Listes(),rect, type );
    }
	
    fclose(file);
}

