#include "enemy_bullet.h"
#include <math.h>

enemy_bullet *createEnemyBullet(int x,int y, int playerX, int playerY,int damage,Sprite *sp){
    enemy_bullet *p = (enemy_bullet *)malloc(sizeof(*p));
    if(p == NULL)
        return NULL;
    p->x = x;
    p->y = y;
    p->playerX = playerX;
    p->playerY = playerY;
    p->damage = damage;
    p->sprite = sp;
    p->dx = playerX - x;
    p->dy = playerY - y;
    
    float norm = sqrt(p->dx * p->dx + p->dy * p->dy);
    if (norm != 0) { 
        p->dx = p->dx / norm;
        p->dy = p->dy / norm;
    }

    return p;
}
void destroyEnemyBullets(enemy_bullet *p){
    if(p->x < 0 || p->x > 1024 || p->y < 0 || p->y > 768)
        free(p);
}

void moveEnemyBullet(enemy_bullet *p){
    int speed = 15;
    p->x += speed* p->dx;
    p->y += speed* p->dy;
}

