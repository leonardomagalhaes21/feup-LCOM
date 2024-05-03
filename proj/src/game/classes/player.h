#ifndef PLAYER_H_
#define PLAYER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "game/sprite/sprite.h"
struct player
{
    int life;
    int damage;
    int x;
    int y;
    Sprite *sprite;
};

struct player *(createPlayer)(int life,int damage,int x,int y, Sprite *sp);



#endif

