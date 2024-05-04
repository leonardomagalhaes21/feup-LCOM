#ifndef MOUSE_CURSOR_H_
#define MOUSE_CURSOR_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "game/sprite/sprite.h"


typedef struct 
{
    int x;
    int y;
    Sprite *sprite;
} MouseCursor;
MouseCursor *createMouseCursor(int x,int y, Sprite *sp);


#endif
