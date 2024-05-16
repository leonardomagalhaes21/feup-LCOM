#ifndef BULLET_H_
#define BULLET_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "game/sprite/sprite.h"


typedef struct
{
    int x;
    int y;
    int mouseX;
    int mouseY;
    int damage;
    float dx;
    float dy;
    Sprite *sprite;
} bullet;

bullet *createBullet(int x,int y, int mouseX, int mouseY,int damage,Sprite *sp);
void destroyBullets(bullet *p);
void moveBullet(bullet *p);
#endif
