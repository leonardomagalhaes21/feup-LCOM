/* #ifndef BULLET_NODE_H_
#define BULLET_NODE_H_


#include "bullet.h"
#include <math.h>
#include <stdlib.h>

typedef struct bullet_node {
    bullet *shot;
    struct bullet_node *next;
} bullet_node;

bullet_node *createBulletNode(bullet *shot);

void destroyBulletNode(bullet_node *node);

void destroyAllBullets(bullet_node *head);
void addBullet(bullet_node **head, bullet *shot);

void removeBullet(bullet_node **head, bullet_node *node_to_remove);

#endif
 */
