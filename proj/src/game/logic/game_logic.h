#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#include "game/classes/player.h"
#include "game/classes/enemy.h"
#include "game/classes/mouse_cursor.h"
#include "game/sprite/sprite.h"

void update_player_logic(player *player, MouseCursor *mouse, bool key_a_pressed, bool key_d_pressed, bool key_w_pressed, int8_t *speed_x, int8_t *speed_y);
void update_enemy_logic(MouseCursor *mouse, enemy *monsters, bool create_enemy);



#endif /* __GAME_LOGIC_H */

