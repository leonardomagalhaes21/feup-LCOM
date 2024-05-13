#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#include "game/classes/player.h"
#include "game/classes/mouse_cursor.h"

void update_game_logic(player *player, MouseCursor *mouse, bool key_a_pressed, bool key_d_pressed, bool key_w_pressed, int8_t *speed_x, int8_t *speed_y);

#endif /* __GAME_LOGIC_H */
