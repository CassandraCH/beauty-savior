/**
 * \file texture.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les textures (affichage)
 * \brief Chargement des images, des textures, des textes et destruction des textures
 */
#include "baseGame.h"

SDL_Texture * texture; /**< Texture pour les ennemis */
SDL_Texture * itemTex; /**< Texture pour les pièces */
SDL_Texture * rockTex; /**< Texture pour les cailloux */
SDL_Texture * treeTex; /**< Texture pour les branches */
SDL_Texture * osTex;   /**< Texture pour les os */
SDL_Texture * passportTex; /**< Texture pour le passport */


/** 
 * \fn bool chargerImage(Texture_Manager * tex,const char * filename )
 * \brief Fonction qui permet de charger une image dans une texture
 * \param tex pointeur sur la texture dans laquelle on veut charger l'image
 * \param filename nom du fichier de l'image
 * \return un booleen : VRAI si l'image a bien ete chargee dans la texture, FAUX sinon
 */
bool chargerImage(Texture_Manager * tex, const char * filename )
{
    printf("Charger image\n");

    //Surface tampom => chargement de l'image 
    SDL_Surface* pTempSurface = IMG_Load( filename );

    //Si l'image n'a pas ete charge dans la surface => retourner FAUX
    if(pTempSurface == 0)
    {
        return false;
    }

    //Transformation de la surface en texture => texture tampon
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(getRenderer() , pTempSurface);

    tex->w = pTempSurface->w;
    tex->h = pTempSurface->h;

    //Si la texture a bien ete creee => Retourner VRAI
    if(pTexture != 0)
    {
        //Supprimer la surface tampon
        SDL_FreeSurface(pTempSurface);
        //Mettre la texture tempon dans la texture passee en parametre
        tex->texture = pTexture;

        return true;
    }

    SDL_DestroyTexture( pTexture );
    return false;
}

/** 
 * \fn extern void ChargerTextureManager(Texture_Manager *tex, char * filepath )
 * \brief Fonction qui permet de charger une texture
 * \param tex pointeur sur la texture dans laquelle on veut charger l'image
 * \param filepath nom du fichier de l'image
 * \return pas de valeur de retour (void)
 */
extern void ChargerTextureManager(Texture_Manager *tex, char * filepath )
{
    printf("Chargement texture DECOR\n");
    
    LibererRessources( tex );

    //Surface tampon => chargement de l'image
    SDL_Surface *surface = IMG_Load(filepath);
    
    //On verifie que le fichier existe bien
    if( !surface )
    {
        printf("Cannot find %s..\n",filepath);
        SDL_Quit();
        exit(1);
    }

    //Sinon, on transforme la surface en texture
    else 
    {

        tex->texture = SDL_CreateTextureFromSurface(getRenderer(), surface);

        //On verifie que le texture a bien ete creee
        if( tex->texture == NULL )
        {
            printf("Erreur: %s\n",filepath);
        }
    }

    //Suppression de la surface tampon
    SDL_FreeSurface(surface); 
}

/** 
 * \fn extern SDL_Texture *ChargerTexture( char * filepath )
 * \brief Fonction qui permet de charger une texture a partir d'une image
 * \param filepath chemin pour acceder a l'image
 * \return un pointeur sur une texture SDL (SDL_Texture)
 */
extern SDL_Texture *ChargerTexture( char * filepath )
{
    //Creation de la texture
    SDL_Texture *texture = NULL;

    //Surface tampon => chargement de l'image
    SDL_Surface *surface = IMG_Load(filepath);

    //On verifie que la surface a bien ete chargee
    if( !surface )
    {
        printf("Cannot find %s..\n",filepath);
        SDL_Quit();
        exit(1);
    }

    //Si la surface a bien chargee
    else 
    {   
        //Transformation de la surface en texture
        texture = SDL_CreateTextureFromSurface(getRenderer(), surface);

        //On verifie que la texture a bien ete creee
        if( !texture )
             printf("Erreur: %s",filepath);
    }

    //Suppression de la surface tampon
    SDL_FreeSurface(surface);

    //On retourne la texture
    return texture;
}

/** 
 * \fn extern void LibererRessources( Texture_Manager *tex )
 * \brief Fonction qui permet detruire une texture
 * \param tex pointeur sur la texture a detruire
 * \return pas de valeur de retour (void)
 */
extern void LibererRessources( Texture_Manager *tex )
{
    if( tex->texture  != NULL )
    {
           SDL_DestroyTexture(tex->texture);
           tex->texture = NULL;
    }    
    
}


/**
 * \fn extern void Init_Textures()
 * \brief Fonction qui charge les textures des ennemis, des pièces, des cailloux, des branches et des os
 * \return pas de valeur de retour (void)
*/
extern void Init_Textures()
{
  texture = ChargerTexture("graphics_assets/enemi.png");
  itemTex = ChargerTexture("graphics_assets/coin.png");
  rockTex = ChargerTexture("graphics_assets/tex_rock.png");
  treeTex = ChargerTexture("graphics_assets/tex_tree.png");
  osTex = ChargerTexture("graphics_assets/tex_os.png");   
  passportTex = ChargerTexture("graphics_assets/passport.png");  
  getBaseGame()->passportReq = ChargerTexture("graphics_assets/passport_requis.png");
}

/**
 * \fn extern void Nettoyers_Textures()
 * \brief Fonction qui détruit les textures des ennemis, des pièces, des cailloux, des branches et des os
 * \return pas de valeur de retour (void)
*/
extern void Nettoyers_Textures()
{
  SDL_DestroyTexture( texture );
  SDL_DestroyTexture( itemTex );
  SDL_DestroyTexture( rockTex );
  SDL_DestroyTexture( treeTex );
  SDL_DestroyTexture( osTex );
  SDL_DestroyTexture( passportTex );
  SDL_DestroyTexture( getBaseGame()->passportReq );
}
