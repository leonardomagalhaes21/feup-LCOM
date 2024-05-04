#ifndef PLAYER_H_
#define PLAYER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "game/sprite/sprite.h"
typedef struct
{
    int life;
    int damage;
    int x;
    int y;
    Sprite *sprite;
} player;

player *(createPlayer)(int life,int damage,int x,int y, Sprite *sp);



#endif

