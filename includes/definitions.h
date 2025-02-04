/**
 * \file definitions.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Fichier regroupant toutes les déclarations globales du jeu.
 */

/*######## GETTER & SETTER ######## */

/*! \addtogroup Getter
*   
 */
///@{
    /**< fonction SDL_Window qui gere la fenetre*/
    extern SDL_Window* getWindow(void);  
    /**< fonction Base_Game*/
    extern Base_Game*  getBaseGame(void); 

    extern LinkedList* getEnnemis(void);            /**< fonction getEnnemis qui gere les ennemis*/
    extern LinkedList* getCollider(void);           /**< fonction getCollider*/
    extern LinkedList* getItems(void);              /**< fonction getItems*/
    extern LinkedList* getBullets(void);            /**< fonction getBullets*/

    extern HUD* getScores(void);                    /**< fonction getScores qui gere le scores*/
    extern HUD* getNiveau();                        /**< fonction getNiveau qui gere les niveaux*/
    extern HUD* getTime();                          /**< fonction getNiveau qui gere le timer du jeux*/
    extern HUD* getItem(int num_item) ;             /**< fonction getItem*/
    extern HUD* getNombreVie();                     /**< fonction getNombreVie*/

    extern GameObject* getGameObject(void);         /**< fonction getMenu*/
    extern GameObject * getHelp(void);              /**< fonction getHelp*/
    extern GameObject* getInventaire(void);         /**< fonction getInventaire*/
    extern GameObject* getInterface(void);          /**< fonction getInterface*/
    extern GameObject * getMenuLoad(void);          /**< fonction getMenuLoad*/
    extern GameObject * getMenuCon(void);           /**< fonction getMenuCon*/
    extern GameObject * getMenuPause(void);         /**< fonction getMenuPause*/
    extern GameObject * getMenu_Win(void);          /**< fonction getMenu_Win*/
    extern GameObject * getMenu_Over(void);         /**< fonction getMenu_Over*/


    extern int getOs();/**< fonction getOs*/
    extern int getRock( );/**< fonction getRock*/
    extern int getBranche();/**< fonction getBranche*/

///@}



extern void Input_InGame(SDL_Event *event); /**< fonction Input_InGame*/
extern void delay(unsigned int frameLimit);
extern void Init_Textures();    /**< fonction d'initialisation des textures pour les entités*/
extern void Clean_Textures();   /**< fonction de nettoyage des textures pour les entités*/

/*######## LISTES ######## */

/*! \addtogroup Listes
*   \brief Listes utilisées dans le programme
 * */
    ///@{ 
    extern LinkedList listEnnemis;  /**<  Listes des ennemis */
    extern LinkedList listCollider; /**< Liste des collisions */
    extern LinkedList bullet;       /**< Liste des bullets */
    extern LinkedList items;        /**< Liste des items */

///@}


extern int tempsEcoule;/**< les temps ecouler*/
extern SDL_Rect camera;/**< la camera*/



/*######## TEXTURE PRINCIPALE DES ELEMENTS DU JEUX ######*/

extern SDL_Texture * texture; /**< Texture pour les ennemis */
extern SDL_Texture * itemTex; /**< Texture pour les pièces */
extern SDL_Texture * rockTex; /**< Texture pour les cailloux */
extern SDL_Texture * treeTex; /**< Texture pour les branches */
extern SDL_Texture * osTex;   /**< Texture pour les os */
extern SDL_Texture * passportTex; /**< Texture pour le passport */



/*####### FONCTION PRINCIPAL ############ */
extern void Init(const char *title); /**< Initialisation */
extern void ProcessInput(SDL_Event* event);/**< fonction ProcessInput*/
extern void Update();        /**< Mise a jour avec le delta-time */
extern void Game_Render();           /**< Gestion du rendu */

extern void Game_DestroyRessources(); /**< Libération de toutes les ressources du jeu */
