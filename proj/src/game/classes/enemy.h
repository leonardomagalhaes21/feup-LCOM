
#ifndef ENEMY_H_
#define ENEMY_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "game/sprite/sprite.h"
typedef struct
{
    int life;
    int damage;
    int x;
    int y;
    int speed_x;
    int speed_y;
    Sprite *sprite;
} enemy;

enemy *createEnemy(int life,int damage,int x,int y,int speed_x,int speed_y, Sprite *sp);

#endif
