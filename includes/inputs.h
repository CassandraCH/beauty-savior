#ifndef __INPUT_H_
#define __INPUT_H_

#include "commun.h"




typedef struct input
{
    bool left, right, up, down, jump, attack, enter, erase, pause, escape;
    SDL_Event event;
 
} Input;


typedef enum {
    IS_RELEASED = 0,
    IS_ONCE,
    IS_PRESSED
}InputState;



// extern void eventLoop();
// // Event Handlers
// extern void onKeyboardEvent(const SDL_KeyboardEvent* e);

// // Keyboard Functions
// // Initialize Keyboard
// extern void initKeyboard();

// // return true if keyState[code] equal to IS_ONCE
// extern bool keyHit(SDL_Scancode code);
// // return true if keyState[code] equal to IS_ONCE or to IS_PRESSED
// extern bool keyPress(SDL_Scancode code);

// void checkIsOnce();

extern void ProcessInput(SDL_Event* event);



#endif