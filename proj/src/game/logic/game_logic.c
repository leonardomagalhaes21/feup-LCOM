#include "game_logic.h"
#include <stdlib.h>

bool is_falling = true;
float cuphead_offset = 0;
enemy monsters[10];
enemy monster_fly;
extern vbe_mode_info_t info;
extern GameState currentState;
bool facingLeft=false;
extern int score;


void update_player_logic(player *player, MouseCursor *mouse, bool key_a_pressed, bool key_d_pressed, bool key_w_pressed, int8_t *speed_x, int8_t *speed_y, int *unvulnerability) {

    if (key_d_pressed || key_a_pressed) {
        if (key_a_pressed) {
            facingLeft = true;
        }
        else if (key_d_pressed) {
            facingLeft = false;
        }
        if (cuphead_offset == 0){
            player->sprite = cuphead1;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 1){
            player->sprite = cuphead2;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 2){
            player->sprite = cuphead3;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 3){
            player->sprite = cuphead4;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 4){
            player->sprite = cuphead5;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 5){
            player->sprite = cuphead6;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 6){
            player->sprite = cuphead7;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 7){
            player->sprite = cuphead8;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 8){
            player->sprite = cuphead9;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 9){
            player->sprite = cuphead10;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 10){
            player->sprite = cuphead11;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 11){
            player->sprite = cuphead12;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 12){
            player->sprite = cuphead13;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 13){
            player->sprite = cuphead14;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 14){
            player->sprite = cuphead15;
            cuphead_offset += 0.5;
        }
        else if (cuphead_offset == 15){
            player->sprite = cuphead16;
            cuphead_offset = 0;
        }
        else{
            cuphead_offset += 0.5;
        } 
    } else {
        player->sprite = cupheadstand;
        cuphead_offset = 0;
    }
    
    int8_t gravity = 4;
    int8_t jump_force = -40; 

    if (is_falling) {
        *speed_y += gravity;
    }

    player->y += *speed_y;

    if (player->y >= 570) {
        player->y = 570;
        *speed_y = 0;
        is_falling = false;
    }

    if (key_a_pressed) {
        *speed_x = -6; 
    } else if (key_d_pressed) {
        *speed_x = 6; 
    } else {
        *speed_x = 0; 
    }
    player->x += *speed_x;

    if (key_w_pressed && !is_falling) {
        is_falling = true;
        *speed_y = jump_force; 
    }
    if(player->x < -30){
        player->x = -30;
    }
    if(player->x > 1045){
        player->x = 1045;
    }
    
    if (key_a_pressed || facingLeft) {
        draw_reverse_sprite(player->sprite, player->x, player->y);
    }
    else {
        draw_sprite(player->sprite, player->x, player->y);
    }

    for (int i = 0; i < 10; i++) {
        if (monsters[i].alive) {  

            bool flag = check_collision(player->sprite, player->x, player->y, monsters[i].sprite, monsters[i].x, monsters[i].y);
            if (flag && *unvulnerability > 60) {
            player->life--;
            *unvulnerability = 0;
            if(player->life == 0){
                currentState = SCOREBOARD;
                save_score(score);
                player->life = 5;
                player->x = 400;
                player->y = 571;
            }
            }
        }
    }
    
}




void update_enemy_logic(MouseCursor *mouse, bool create_enemy) {
    if (create_enemy) {
        for (int i = 0; i < 10; i++) {
            if (!monsters[i].alive) {
                int spawn_side = rand() % 2; 
                int spawn_x;
                if (spawn_side == 0) {
                    spawn_x = -monsters[i].sprite->width; 
                    monsters[i].speed_x = 2; 
                } else {
                    spawn_x = info.XResolution;
                    monsters[i].speed_x = -2;
                }
                reviveEnemy(&monsters[i], spawn_x, 650);
                monsters[i].speed_y = 0; 
                break;
            }
        }
    }

    int8_t gravity = 4;

    for (int i = 0; i < 10; i++) {
        if (monsters[i].alive) {
            monsters[i].y += monsters[i].speed_y;
            monsters[i].speed_y += gravity;

            if (monsters[i].y >= 600) {
                monsters[i].y = 600;
                monsters[i].speed_y = 0;
            }

            monsters[i].x += monsters[i].speed_x;
            if (monsters[i].x < -monsters[i].sprite->width || monsters[i].x >= info.XResolution) {
                monsters[i].alive = false; 
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (monsters[i].alive) {
            monsters[i].y += monsters[i].speed_y;
            monsters[i].speed_y += gravity;

            if (monsters[i].y >= 600) {
                monsters[i].y = 600;
                monsters[i].speed_y = 0;
            }

            monsters[i].x += monsters[i].speed_x;
            if (monsters[i].x < -monsters[i].sprite->width) {
                monsters[i].x = -monsters[i].sprite->width;
                monsters[i].speed_x = abs(monsters[i].speed_x); 
            } else if (monsters[i].x >= info.XResolution) {
                monsters[i].x = info.XResolution - 1; 
                monsters[i].speed_x = -abs(monsters[i].speed_x); 
            }

            
        
        }
    }
    for (int i = 0; i < 10; i++) {
        if (monsters[i].alive) {
            draw_sprite(monsters[i].sprite, monsters[i].x, monsters[i].y);
        }
    }

    if (monster_fly.alive && monster_fly.life > 0)
        draw_reverse_sprite(monster_fly.sprite, monster_fly.x, monster_fly.y);
    
}




void update_bullet_logic(bullet_node **head) {
    bullet_node *prev = NULL;
    bullet_node *current = *head;
    
    while (current != NULL) {
        moveBullet(current->shot);
        draw_sprite(current->shot->sprite, current->shot->x, current->shot->y);

        if (current->shot->x < 0 || current->shot->x >= info.XResolution || current->shot->y < 0 || current->shot->y >= info.YResolution) {
            bullet_node *to_remove = current;
            current = current->next;

            if (prev == NULL) {
                *head = current;
            } else {
                prev->next = current;
            }

            destroyBulletNode(to_remove);
        } else {
            prev = current;
            current = current->next;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (monsters[i].alive) {
            current = *head;
            prev = NULL; 
            while (current != NULL) {
                bool flag = check_collision(current->shot->sprite, current->shot->x, current->shot->y, monsters[i].sprite, monsters[i].x, monsters[i].y);
                if (flag) {
                    monsters[i].alive = false;
                    bullet_node *to_remove = current;

                    if (prev == NULL) {
                        *head = current->next;
                    } else {
                        prev->next = current->next;
                    }

                    current = current->next;
                    destroyBulletNode(to_remove);
                    break;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        }
    }

    if (monster_fly.alive) {
        current = *head;
        prev = NULL;
        while (current != NULL) {
            bool flag = check_collision(current->shot->sprite, current->shot->x, current->shot->y, monster_fly.sprite, monster_fly.x, monster_fly.y);
            if (flag) {
                monster_fly.life -= 3;
                if (monster_fly.life <= 0) {
                    monster_fly.alive = false;
                }
                bullet_node *to_remove = current;

                if (prev == NULL) {
                    *head = current->next;
                } else {
                    prev->next = current->next;
                }

                current = current->next;
                destroyBulletNode(to_remove);
                break;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}
