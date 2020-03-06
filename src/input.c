#include "baseGame.h"




extern Input* get_Input()
{
    return &input;
}



/**
 * Gestion des entrées utilisateurs.
 */ 
extern void ProcessInput(SDL_Event * event)
{

   if (getBaseGame()->state == MENU_PRINCIPAL )
   {
        Input_MenuPrincipal(event);
   }
   else if (getBaseGame()->state == IN_GAME )
   {
       Input_InGame(event);
   }
   

}