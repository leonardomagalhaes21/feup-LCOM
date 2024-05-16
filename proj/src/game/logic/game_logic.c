#include "game_logic.h"

bool is_falling = true;
float cuphead_offset = 0;
enemy monsters[10];

void update_player_logic(player *player, MouseCursor *mouse, bool key_a_pressed, bool key_d_pressed, bool key_w_pressed, int8_t *speed_x, int8_t *speed_y) {

    if (key_d_pressed || key_a_pressed) {
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
    
    if (key_a_pressed) {
        draw_reverse_sprite(player->sprite, player->x, player->y);
    }
    else {
        draw_sprite(player->sprite, player->x, player->y);
    }
    
}


void update_enemy_logic(MouseCursor *mouse, bool create_enemy) {
    if (create_enemy) {
        for (int i = 0; i < 10; i++) {
            if (monsters[i].alive == false) {
                reviveEnemy(&monsters[i],5,5);
                break;
            }
        }
    }

    int8_t gravity = 4;
    
    for (int i = 0; i < 10; i++) {
        if (monsters[i].alive ==true) {
            monsters[i].y += monsters[i].speed_y;
            monsters[i].speed_y += gravity;

            if (monsters[i].y >= 500) {
                monsters[i].y = 550;
                monsters[i].speed_y = 0;
            }
            monsters[i].x += monsters[i].speed_x;
            if (monsters[i].x < -30) {
                monsters[i].x = -30;    
                monsters[i].speed_x = -monsters[i].speed_x;
            }
        }
    }

    for(int i = 0; i < 10; i++){
        if (monsters[i].alive == true) {
            draw_sprite(monsters[i].sprite, monsters[i].x, monsters[i].y);
            
        }
    }
}





