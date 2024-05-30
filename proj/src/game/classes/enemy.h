
#ifndef ENEMY_H_
#define ENEMY_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "game/sprite/sprite.h"
#include "game/classes/enemy_bullet.h"
typedef struct
{
    int life;
    int damage;
    int x;
    int y;
    int speed_x;
    int speed_y;
    Sprite *sprite;
    bool alive;
    enemy_bullet *shot;
} enemy;

enemy *createEnemy(int life,int damage,int x,int y,int speed_x,int speed_y, Sprite *sp,bool alive);
enemy *createEnemyWithDefaultShot(int life, int damage, int x, int y, int speed_x, int speed_y, Sprite *sp, bool alive);
void destroyEnemy(enemy *p);


void reviveEnemy(enemy *p,int x,int y);

#endif
