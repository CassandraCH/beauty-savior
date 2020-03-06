#include "chargeSave.h"


extern void ChargerPartie()
{
    FILE * file = fopen("files_assets/data.txt", "r");
    
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

extern void SauvegarderPartie()
{
    FILE * file = fopen("files_assets/data.txt", "a");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }

    fprintf(file,"%f %f", getPlayer()->x , getPlayer()->y );
    
    fclose(file);
}

extern void SaveCollider_Position()
{
    FILE * file = fopen("files_assets/niveau1_position.txt", "w");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    Node * pt;
    
    if( getCollider()->nodeCount  > 0 )
    {
        for( pt =  getCollider()->tete; pt != NULL; pt = pt->suivant )
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
    
    if( getCollider()->nodeCount  > 0 )
    {
        for( pt = getCollider()->tete ; pt != NULL; pt = pt->suivant )
        {
            if (fscanf(file, "%d %d",&pt->rect->x , &pt->rect->y) )
            {}
        }
    }

    fclose(file);
}

extern void Chargement_CreationPNJ(LinkedList*lst, char * filename)
{
    FILE * file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    int typeCollider;

    while( !feof(file) )
    {
        SDL_Rect *rect = malloc( sizeof(SDL_Rect));       
        if( fscanf(file, "%d %d %d %d %d",&typeCollider, &rect->x , &rect->y, &rect->w, &rect->h) )
        {
            insertion(lst, rect, typeCollider);
        }
    }
	
    fclose(file);
}

extern void ChargementItems(const char * filename, SDL_Texture * tex)
{
    FILE * file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    int w, h;
    SDL_QueryTexture(tex, NULL,NULL, &w, &h );
    while( !feof(file) )
    {
        SDL_Rect *rect = malloc( sizeof(SDL_Rect));
        rect->w = w;
        rect->h = h;             
        if( fscanf(file, "%d %d",&rect->x , &rect->y) ){
            insertion(getItems(),  rect, item );
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
            insertion(getEnnemis(),  rect, ennemi );
        }
    }

    fclose(file);
}
