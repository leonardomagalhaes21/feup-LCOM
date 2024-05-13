#include "enemy.h"

enemy *createEnemy(int life,int damage,int x,int y,int speed_x,int speed_y, Sprite *sp){
    enemy *p = (enemy *)malloc(sizeof(*p));
    if(p == NULL)
        return NULL;
    p->life = life;
    p->damage = damage;
    p->x = x;
    p->y = y;
    p->sprite = sp;
    return p;
}
