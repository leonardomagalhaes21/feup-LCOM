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

#include "xpm/font/PressStart2P-vaV7.xpm"

#include "xpm/resolutionModes/14C/hearth2.xpm"
#include "xpm/resolutionModes/14C/mouse.xpm"
#include "xpm/resolutionModes/14C/square.xpm"
#include "xpm/resolutionModes/14C/backgrounds/full_Menu.xpm"
#include "xpm/resolutionModes/14C/backgrounds/background.xpm"
#include "xpm/resolutionModes/14C/backgrounds/ScoreBoardBackgrd.xpm"
#include "xpm/resolutionModes/14C/backgrounds/LeaderboardMenu.xpm"
#include "xpm/resolutionModes/14C/monster1.xpm"
#include "xpm/resolutionModes/14C/monster2.xpm"
#include "xpm/resolutionModes/14C/bala.xpm"


#include "xpm/resolutionModes/11A/hearth2_11A.xpm"
#include "xpm/resolutionModes/11A/square11A.xpm"
#include "xpm/resolutionModes/11A/backgrounds/full_Menu11A.xpm"
#include "xpm/resolutionModes/11A/backgrounds/background11A.xpm"
#include "xpm/resolutionModes/11A/backgrounds/ScoreBoardBackgrd11A.xpm"
#include "xpm/resolutionModes/11A/backgrounds/LeaderboardMenu11A.xpm"
#include "xpm/resolutionModes/11A/monster1_11A.xpm"
#include "xpm/resolutionModes/11A/monster2_11A.xpm"
#include "xpm/resolutionModes/11A/bala11A.xpm"

#include "xpm/resolutionModes/110/hearth2_110.xpm"
#include "xpm/resolutionModes/110/square_110.xpm"
#include "xpm/resolutionModes/110/backgrounds/full_Menu_110.xpm"
#include "xpm/resolutionModes/110/backgrounds/background_110.xpm"
#include "xpm/resolutionModes/110/backgrounds/ScoreBoardBackgrd_110.xpm"
#include "xpm/resolutionModes/110/backgrounds/LeaderboardMenu_110.xpm"
#include "xpm/resolutionModes/110/monster1_110.xpm"
#include "xpm/resolutionModes/110/monster2_110.xpm"
#include "xpm/resolutionModes/110/bala_110.xpm"

#include "xpm/resolutionModes/115/hearth2_115.xpm"
#include "xpm/resolutionModes/115/square_115.xpm"
#include "xpm/resolutionModes/115/backgrounds/full_Menu_115.xpm"
#include "xpm/resolutionModes/115/backgrounds/background_115.xpm"
#include "xpm/resolutionModes/115/backgrounds/ScoreBoardBackgrd_115.xpm"
#include "xpm/resolutionModes/115/backgrounds/LeaderboardMenu_115.xpm"
#include "xpm/resolutionModes/115/monster1_115.xpm"
#include "xpm/resolutionModes/115/monster2_115.xpm"
#include "xpm/resolutionModes/115/bala_115.xpm"


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
void loadAllSprites(uint16_t mode);
int clean_img(uint16_t x, uint16_t y, uint16_t width);
int drawChar(char c, uint16_t x, uint16_t y);
int drawNum(int c, uint16_t x, uint16_t y);
int drawTxt(char txt[], uint16_t x, uint16_t y);

bool check_collision(Sprite *sp1, int x1, int y1, Sprite *sp2, int x2, int y2);

//void freeAllSprites();

#endif

