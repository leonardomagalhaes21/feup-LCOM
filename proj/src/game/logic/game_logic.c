#include "game_logic.h"
bool is_falling = true;
void update_player_logic(player *player, MouseCursor *mouse, bool key_a_pressed, bool key_d_pressed, bool key_w_pressed, int8_t *speed_x, int8_t *speed_y) {
    
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
    draw_sprite(player->sprite, player->x, player->y); 
}


void update_enemy_logic(MouseCursor *mouse, enemy *monsters, bool create_enemy) {
    
    if (create_enemy) {
        for (int i = 0; i < 10; i++) {
            if (&monsters[i] == NULL) {
                monsters[i] = *createEnemy(5, 5, 400, 571,2,2, monster1);
                break;
            }
        }
    }

    int8_t gravity = 4;
    for (int i = 0; i < 10; i++) {
        if (&monsters[i] != NULL) {
            monsters[i].y += monsters[i].speed_y;
            monsters[i].speed_y += gravity;

            if (monsters[i].y >= 300) {
                monsters[i].y = 400;
                monsters[i].speed_y = 0;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (&monsters[i] != NULL && monsters[i].life <= 0) {
            free(&monsters[i]);
        }
    }
    for(int i = 0; i < 10; i++){
        if (&monsters[i] != NULL) {
            draw_sprite(monsters[i].sprite, monsters[i].x, monsters[i].y);
        }
    }
}

