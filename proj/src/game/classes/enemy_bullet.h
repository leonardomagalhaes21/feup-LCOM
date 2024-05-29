#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "game/sprite/sprite.h"


typedef struct
{
    int x;
    int y;
    int playerX;
    int playerY;
    int damage;
    float dx;
    float dy;
    Sprite *sprite;
} enemy_bullet;

enemy_bullet *createEnemyBullet( int x, int y,int playerX, int playerY,int damage,Sprite *sp);
void destroyEnemyBullets(enemy_bullet *p);
void moveEnemyBullet(enemy_bullet *p);
#endif
