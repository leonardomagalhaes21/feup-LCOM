#ifndef SPRITE_H_
#define SPRITE_H_

#include "xpm/Cuphead_running.xpm"

#include "xpm/mouse.xpm"
#include "xpm/square.xpm"
#include "xpm/full_Menu.xpm"
#include "xpm/background.xpm"
#include "xpm/monster1.xpm"
#include "devices/graphics/graphics.h"



typedef struct {
    int width, height;
    uint32_t *map;
} Sprite;

Sprite *main_char;
Sprite *mouse_cursor;
Sprite *menu_full;
Sprite *background;
Sprite *monster1;

Sprite *create_sprite(xpm_map_t pic); 
void destroy_sprite(Sprite *sp);
int move_sprite(Sprite *sp);
int draw_sprite(Sprite *sp, int x, int y);
void loadAllSprites();
int clean_img(uint16_t x, uint16_t y, uint16_t width);
/*
static int check_collision(Sprite *sp1, int x1, int y1, Sprite *sp2, int x2, int y2);
void freeAllSprites();
*/

#endif

