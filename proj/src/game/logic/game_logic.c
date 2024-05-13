#include "game_logic.h"
bool is_falling = true;
void update_game_logic(player *player, MouseCursor *mouse, bool key_a_pressed, bool key_d_pressed, bool key_w_pressed, int8_t *speed_x, int8_t *speed_y) {
    
    int8_t gravity = 2;
    int8_t jump_force = -20; 

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
        *speed_x = -3; 
    } else if (key_d_pressed) {
        *speed_x = 3; 
    } else {
        *speed_x = 0; 
    }
    player->x += *speed_x;

    if (key_w_pressed && !is_falling) {
        is_falling = true;
        *speed_y = jump_force; 
    }
}


