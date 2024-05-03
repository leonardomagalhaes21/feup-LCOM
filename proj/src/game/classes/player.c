#include "player.h"

struct player *createPlayer(int life,int damage,int x,int y, Sprite *sp){
    struct player *p = (struct player *)malloc(sizeof(*p));
    if(p == NULL)
        return NULL;
    p->life = life;
    p->damage = damage;
    p->x = x;
    p->y = y;
    p->sprite = sp;
    return p;
}
