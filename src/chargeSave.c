/**
 * \file chargeSave.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le chargement et la sauvegarde des parties
 */
#include "chargeSave.h"

/**
 * \fn extern void ChargerPartie()
 * \brief Fonction qui permet de charger une partie sauvegardee
 * \details Lecture du fichier data.txt
 * \return pas de valeur de retour (void)
*/
extern void ChargerPartie()
{
    //Ouverture du fichier data.txt
    FILE * file = fopen("files_assets/save_player.txt", "r");
    
    //Verification que le fichier existe bien
    if (file == NULL) {
        fprintf(stderr, "Can't open input file in list!\n");
        exit(1);    
    }

    int niveau , nb_objet;
    
    //Lecture dans le fichier des donnees sauvegardees
    if( fscanf(file,"%d %d", &niveau, &nb_objet)  )
    {
        getPlayer()->niveau = niveau;
        getPlayer()->nb_objet = nb_objet;
        printf("%d %d \n", getPlayer()->niveau, getPlayer()->nb_objet);

        
    }
    //Fermeture du fichier
    fclose(file);
}

/**
 * \fn extern void SauvegarderPartie()
 * \brief Fonction qui permet sauvegarder une partie
 * \details Creation du fichier data.txt
 * \return pas de valeur de retour (void)
*/
extern void SauvegarderPartie()
{
    //Ouverture ou creation du fichier data.txt
    FILE * file = fopen("files_assets/save_player.txt", "w");
    
    //Gestion des erreurs de creation du fichier
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }

    //Sauvegarder la position en x et y du joueur
    fprintf(file,"%d %d", getPlayer()->niveau, getPlayer()->nb_objet);
    
    //Fermeture du fichier
    fclose(file);
}

/**
 * \fn extern void SaveCollider_Position()
 * \brief Fonction qui permet sauvegarder la position des colliders dans un fichier
 * \details Creation d'un fichier
 * \details Utilisation d'un pointeur pour pouvoir parcourir la liste de colliders
 * \return pas de valeur de retour (void)
*/
extern void SaveCollider_Position()
{
    //Ouverture ou creation du fichier niveau1_position.txt
    FILE * file = fopen("files_assets/niveau1_position.txt", "w");
    
    //Gestion des erreurs de creation du fichier
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }

    Node *pt; // Pointeur utilise pour parcourir la liste de colliders 

    //Ecrire la position en x et en y des colliders dans le fichier
    if( getCollider()->nodeCount  > 0 )
    {
        //Parcours de la liste de colliders
        for( pt =  getCollider()->tete; pt != NULL; pt = pt->suivant )
        {
            //Ecrire la position en x et en y du collider actuel dans le fichier
            fprintf(file,"%d %d\n", pt->rect->x , pt->rect->y );
        }
    }

    //Fermeture du fichier
    fclose(file);
}

/**
 * \fn extern void ChargementCollider(const char * filename) 
 * \brief Fonction qui permet de charger les colliders a partir d'un fichier
 * \details Utilisation d'un pointeur pour pouvoir parcourir la liste des colliders
 * \param filename Nom du fichier ou la position des colliders est sauvegardee
 * \return pas de valeur de retour (void)
*/
extern void ChargementCollider(const char * filename) 
{
    //Ouverture du fichier 
    FILE * file = fopen(filename, "r");
    
    //Gestion des erreurs d'ouverture du fichier
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    Node *pt; //Pointeur utilise pour parcourir la liste de colliders 

    //Parcours de la liste si il y a au moins un collider
    if( getCollider()->nodeCount  > 0 )
    {
        //Parcours de la liste de colliders
        for( pt = getCollider()->tete ; pt != NULL; pt = pt->suivant )
        {
            //Lecture des positions en x et en y dans le fichier
            if (fscanf(file, "%d %d",&pt->rect->x , &pt->rect->y) );            
        }
    }

    //Fermeture du fichier
    fclose(file);
}

/**
 * \fn extern void Chargement_CreationPNJ(LinkedList*lst, char * filename)
 * \brief Fonction qui permet de charger et créer toutes les entités (sauf le joueur) a partir d'un fichier
 * \param lst Liste des elements
 * \param filename Nom du fichier
 * \return pas de valeur de retour (void)
*/
extern void Chargement_CreationPNJ(LinkedList * lst, char * filename)
{
    //Si il y a deja des elements dans la liste => les supprimer
    if( lst->nodeCount > 0 ) 
    {
        suppListe(lst);
    }

    //Ouverture du fichier
    FILE * file = fopen(filename, "r");

    //Gestion des erreurs d'ouverture du fichier
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    
    int typeCollider; // Variable qui permet de savoir le type du collider 

    while( !feof(file) )
    {
        //Creation d'un rectangle en SDL pour chaque entite => Allocation dynamique
        SDL_Rect *rect = malloc(sizeof(SDL_Rect)); 
        //Lecture du type, des positions en x et en y, de la largeur et de la hauteur du collider  
        if( fscanf(file, "%d %d %d %d %d",&typeCollider, &rect->x , &rect->y, &rect->w, &rect->h) )
        {
            //Ajout dans la liste (lst) les proprietes du collider d
            insertion(lst, rect, typeCollider, false);
        }
    }
	
    //Fermeture d'un fichier
    fclose(file);
}

/**
 * \fn extern void ChargementItems(const char * filename, SDL_Texture * tex)
 * \brief Fonction qui permet de charger les items a partir d'un fichier
 * \param filename Nom du fichier
 * \param tex Texture de l'item
 * \return pas de valeur de retour (void)
*/
extern void ChargementItems(const char * filename, SDL_Texture * tex)
{

    //Ouverture du fichier

    FILE * file = fopen(filename, "r");
    
    //Gestion des erreurs d'ouverture du fichier
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }

    int w, h; //Largeur et hauteur de l'item
    SDL_QueryTexture(tex, NULL,NULL, &w, &h );

    //Tant qu'on n'a pas lu entierement le fichier
    while( !feof(file) )
    {
        SDL_Rect *rect = malloc( sizeof(SDL_Rect));
        rect->w = w;
        rect->h = h;    
        //Recuperation des positions en x et y de l'item dans le fichier         
        if( fscanf(file, "%d %d",&rect->x , &rect->y) ){
            //Ajout de l'item avec les proprietes recuperees dans le fichier
            insertion(getItems(),  rect, item , false);
        }
    }

    //Fermeture du fichier
    fclose(file);
}

/**
 * \fn extern void ChargementEnnemis(const char * filename)
 * \brief Fonction qui permet de charger les ennemis a partir d'un fichier
 * \param filename Nom du fichier
 * \return pas de valeur de retour (void)
*/
extern void ChargementEnnemis(const char * filename)
{
    //Ouverture du fichier
    FILE * file = fopen(filename, "r");
    
    //Gestion des erreurs d'ouverture du fichier
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }
    int actif; //Variable qui permet de stocker l'etat de l'ennemi = actif

    //Tant qu'on n'a pas lu entierement le fichier
    while( !feof(file) )
    {
        SDL_Rect *rect = malloc( sizeof(SDL_Rect));
        rect->w = 55;
        rect->h = 55; 
        //Recuperation des positions en x et en y, et de l'etat de l'ennemi           
        if( fscanf(file, "%d %d %d",&rect->x , &rect->y, &actif ) ){
            //Ajout de l'ennemi avec les proprietes recuperees dans le fichier
            insertion(getEnnemis(),  rect, ennemi , actif );
        }
    }

    //Fermeture du fichier
    fclose(file);
}
