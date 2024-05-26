#ifndef SPRITE_H_
#define SPRITE_H_

#include "xpm/Cuphead_running.xpm"
#include "xpm/cuphead/cuphead1.xpm"
#include "xpm/cuphead/cuphead2.xpm"
#include "xpm/cuphead/cuphead3.xpm"
#include "xpm/cuphead/cuphead4.xpm"
#include "xpm/cuphead/cuphead5.xpm"
#include "xpm/cuphead/cuphead6.xpm"
#include "xpm/cuphead/cuphead7.xpm"
#include "xpm/cuphead/cuphead8.xpm"
#include "xpm/cuphead/cuphead9.xpm"
#include "xpm/cuphead/cuphead10.xpm"
#include "xpm/cuphead/cuphead11.xpm"
#include "xpm/cuphead/cuphead12.xpm"
#include "xpm/cuphead/cuphead13.xpm"
#include "xpm/cuphead/cuphead14.xpm"
#include "xpm/cuphead/cuphead15.xpm"
#include "xpm/cuphead/cuphead16.xpm"
#include "xpm/cuphead/cupheadstand.xpm"
#include "xpm/bala.xpm"
#include "xpm/font/PressStart2P-vaV7.xpm"

#include "xpm/hearth2.xpm"
#include "xpm/mouse.xpm"
#include "xpm/square.xpm"
#include "xpm/full_Menu.xpm"
#include "xpm/background.xpm"
#include "xpm/ScoreBoardBackgrd.xpm"
#include "xpm/LeaderboardMenu.xpm"
#include "xpm/monster1.xpm"
#include "xpm/monster2.xpm"
#include "devices/graphics/graphics.h"



typedef struct {
    int width, height;
    uint32_t *map;
} Sprite;

Sprite *cuphead1;
Sprite *cuphead2;
Sprite *cuphead3;
Sprite *cuphead4;
Sprite *cuphead5;
Sprite *cuphead6;
Sprite *cuphead7;
Sprite *cuphead8;
Sprite *cuphead9;
Sprite *cuphead10;
Sprite *cuphead11;
Sprite *cuphead12;
Sprite *cuphead13;
Sprite *cuphead14;
Sprite *cuphead15;
Sprite *cuphead16;
Sprite *cupheadstand;
Sprite *mouse_cursor;
Sprite *menu_full;
Sprite *background;
Sprite *monster1;
Sprite *monster2;
Sprite *hearthLife;
Sprite *bala;
Sprite *font;
Sprite *ScoreBackGrnd; 
Sprite *LeaderBackGrnd; 

Sprite *create_sprite(xpm_map_t pic); 
void destroy_sprite(Sprite *sp);
int move_sprite(Sprite *sp);
int draw_sprite(Sprite *sp, int x, int y);
int draw_reverse_sprite(Sprite *sp, int x, int y);
void loadAllSprites();
int clean_img(uint16_t x, uint16_t y, uint16_t width);
int drawChar(char c, uint16_t x, uint16_t y);
int drawNum(int c, uint16_t x, uint16_t y);
int drawTxt(char txt[], uint16_t x, uint16_t y);

bool check_collision(Sprite *sp1, int x1, int y1, Sprite *sp2, int x2, int y2);

//void freeAllSprites();

#endif

