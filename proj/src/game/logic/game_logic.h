#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#define FLYMONS1_X 800
#define FLYMONS1_Y 100
#define FLYMONS2_X 100
#define FLYMONS2_Y 200

#include "game/classes/player.h"
#include "game/classes/enemy.h"
#include "game/classes/mouse_cursor.h"
#include "game/sprite/sprite.h"
#include "game/classes/bullet_node.h"
#include "game/classes/enemy_bullet.h"
#include "game/classes/bullet.h"
#include "game/modes/menu.h"
#include "game/logic/save_score.h"

void update_player_logic(player *player, MouseCursor *mouse, bool key_a_pressed, bool key_d_pressed, bool key_w_pressed, int8_t *speed_x, int8_t *speed_y, int *unvulnerability);
void update_enemy_logic(MouseCursor *mouse, bool create_enemy, player *player);
void update_bullet_logic(bullet_node **head);
bool check_enemy_bullet_collisions(player *player,int *unvulnerability);
void spawn_dead_enemies();


#endif /* __GAME_LOGIC_H */

