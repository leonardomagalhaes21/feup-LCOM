/** Creates a new sprite from XPM "pic", with specified
* position (within the screen limits) and speed;
* Does not draw the sprite on the screen
* Returns NULL on invalid pixmap.
*/

#include <lcom/lcf.h>
#include "sprite.h"

extern vbe_mode_info_t info;



Sprite *create_sprite(xpm_map_t pic) {
    Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
    xpm_image_t img;
    
    if( sp == NULL )
    return NULL;
    sp->map = (uint32_t *) xpm_load(pic, XPM_8_8_8_8, &img);
    if( sp->map == NULL ) {
        free(sp);
        return NULL;
    }
    sp->width = img.width; 
    sp->height=img.height;
    return sp;
}

void destroy_sprite(Sprite *sp) {
    if( sp == NULL )
        return;
    if( sp ->map )
    free(sp->map);
    free(sp);
    sp = NULL; 
}
int move_sprite(Sprite *sp) {
    return 1;
}
/* Some useful non-visible functions */
int draw_sprite(Sprite *sp, int x, int y) {
    uint16_t width = sp->width;
    uint16_t height = sp->height;
    for (int w = 0 ; w < width ; w++) {
        for (int h = 0 ; h < height ; h++) {
            if (vg_draw_pixel(x + w, y + h, sp->map[w + h*width])) return 1;
        }
    }
    return 0; 
}

int draw_reverse_sprite(Sprite *sp, int x, int y) {
    uint16_t width = sp->width;
    uint16_t height = sp->height;
    for (int w = 0 ; w < width ; w++) {
        for (int h = 0 ; h < height ; h++) {
            if (vg_draw_pixel(x + (width - w), y + h, sp->map[w + h*width])) return 1;
        }
    }
    return 0; 
}

void loadAllSprites(uint16_t mode){
    
    if(mode==0x14C) {
        cuphead1 = create_sprite((xpm_map_t) cuphead_1);
        cuphead2 = create_sprite((xpm_map_t) cuphead_2);
        cuphead3 = create_sprite((xpm_map_t) cuphead_3);
        cuphead4 = create_sprite((xpm_map_t) cuphead_4);
        cuphead5 = create_sprite((xpm_map_t) cuphead_5);
        cuphead6 = create_sprite((xpm_map_t) cuphead_6);
        cuphead7 = create_sprite((xpm_map_t) cuphead_7);
        cuphead8 = create_sprite((xpm_map_t) cuphead_8);
        cuphead9 = create_sprite((xpm_map_t) cuphead_9);
        cuphead10 = create_sprite((xpm_map_t) cuphead_10);
        cuphead11 = create_sprite((xpm_map_t) cuphead_11);
        cuphead12 = create_sprite((xpm_map_t) cuphead_12);
        cuphead13 = create_sprite((xpm_map_t) cuphead_13);
        cuphead14 = create_sprite((xpm_map_t) cuphead_14);
        cuphead15 = create_sprite((xpm_map_t) cuphead_15);
        cuphead16 = create_sprite((xpm_map_t) cuphead_16);
        cupheadstand = create_sprite((xpm_map_t) cuphead_stand);
        hearthLife = create_sprite((xpm_map_t) hearth2);
        font = create_sprite((xpm_map_t) startFont);
        ScoreBackGrnd = create_sprite((xpm_map_t) ScoreBrdBackgrnd);
        LeaderBackGrnd = create_sprite((xpm_map_t) LeaderbrdBckgrnd);
        mouse_cursor= create_sprite((xpm_map_t) square);
        menu_full = create_sprite((xpm_map_t) full_Menu);
        background = create_sprite((xpm_map_t) back_ground);
        monster1 = create_sprite((xpm_map_t) monster_1);
        monster2 = create_sprite((xpm_map_t) monster_2);
        bala = create_sprite((xpm_map_t) bala1);
    }
    else if (mode==0x11A) {
        cuphead1 = create_sprite((xpm_map_t) cuphead1_11A);
        cuphead2 = create_sprite((xpm_map_t) cuphead2_11A);
        cuphead3 = create_sprite((xpm_map_t) cuphead3_11A);
        cuphead4 = create_sprite((xpm_map_t) cuphead4_11A);
        cuphead5 = create_sprite((xpm_map_t) cuphead5_11A);
        cuphead6 = create_sprite((xpm_map_t) cuphead6_11A);
        cuphead7 = create_sprite((xpm_map_t) cuphead7_11A);
        cuphead8 = create_sprite((xpm_map_t) cuphead8_11A);
        cuphead9 = create_sprite((xpm_map_t) cuphead9_11A);
        cuphead10 = create_sprite((xpm_map_t) cuphead10_11A);
        cuphead11 = create_sprite((xpm_map_t) cuphead11_11A);
        cuphead12 = create_sprite((xpm_map_t) cuphead12_11A);
        cuphead13 = create_sprite((xpm_map_t) cuphead13_11A);
        cuphead14 = create_sprite((xpm_map_t) cuphead14_11A);
        cuphead15 = create_sprite((xpm_map_t) cuphead15_11A);
        cuphead16 = create_sprite((xpm_map_t) cuphead16_11A);
        cupheadstand = create_sprite((xpm_map_t) cupheadstand_11A);
        
        hearthLife = create_sprite((xpm_map_t) hearth2_11A);
        font = create_sprite((xpm_map_t) PressStart2P_vaV7_11A);
        ScoreBackGrnd = create_sprite((xpm_map_t) ScoreBoardBackgrd11A);
        LeaderBackGrnd = create_sprite((xpm_map_t) LeaderboardMenu11A);
        mouse_cursor= create_sprite((xpm_map_t) square11A);
        menu_full = create_sprite((xpm_map_t) full_Menu11A);
        background = create_sprite((xpm_map_t) background11A);
        monster1 = create_sprite((xpm_map_t) monster1_11A);
        monster2 = create_sprite((xpm_map_t) monster2_11A);
        bala = create_sprite((xpm_map_t) bala11A);
    }
    else if (mode==0x115) {
        cuphead1 = create_sprite((xpm_map_t) cuphead1_115);
        cuphead2 = create_sprite((xpm_map_t) cuphead2_115);
        cuphead3 = create_sprite((xpm_map_t) cuphead3_115);
        cuphead4 = create_sprite((xpm_map_t) cuphead4_115);
        cuphead5 = create_sprite((xpm_map_t) cuphead5_115);
        cuphead6 = create_sprite((xpm_map_t) cuphead6_115);
        cuphead7 = create_sprite((xpm_map_t) cuphead7_115);
        cuphead8 = create_sprite((xpm_map_t) cuphead8_115);
        cuphead9 = create_sprite((xpm_map_t) cuphead9_115);
        cuphead10 = create_sprite((xpm_map_t) cuphead10_115);
        cuphead11 = create_sprite((xpm_map_t) cuphead11_115);
        cuphead12 = create_sprite((xpm_map_t) cuphead12_115);
        cuphead13 = create_sprite((xpm_map_t) cuphead13_115);
        cuphead14 = create_sprite((xpm_map_t) cuphead14_115);
        cuphead15 = create_sprite((xpm_map_t) cuphead15_115);
        cuphead16 = create_sprite((xpm_map_t) cuphead16_115);
        cupheadstand = create_sprite((xpm_map_t) cupheadstand_115);

        hearthLife = create_sprite((xpm_map_t) hearth2_115);
        font = create_sprite((xpm_map_t) PressStart2P_vaV7_115);
        ScoreBackGrnd = create_sprite((xpm_map_t) ScoreBoardBackgrd_115);
        LeaderBackGrnd = create_sprite((xpm_map_t) LeaderboardMenu_115);
        mouse_cursor= create_sprite((xpm_map_t) square_115);
        menu_full = create_sprite((xpm_map_t) full_Menu_115);
        background = create_sprite((xpm_map_t) background_115);
        monster1 = create_sprite((xpm_map_t) monster1_115);
        monster2 = create_sprite((xpm_map_t) monster2_115);
        bala = create_sprite((xpm_map_t) bala_115);
    }
    else if (mode==0x110) {
        cuphead1 = create_sprite((xpm_map_t) cuphead1_110);
        cuphead2 = create_sprite((xpm_map_t) cuphead2_110);
        cuphead3 = create_sprite((xpm_map_t) cuphead3_110);
        cuphead4 = create_sprite((xpm_map_t) cuphead4_110);
        cuphead5 = create_sprite((xpm_map_t) cuphead5_110);
        cuphead6 = create_sprite((xpm_map_t) cuphead6_110);
        cuphead7 = create_sprite((xpm_map_t) cuphead7_110);
        cuphead8 = create_sprite((xpm_map_t) cuphead8_110);
        cuphead9 = create_sprite((xpm_map_t) cuphead9_110);
        cuphead10 = create_sprite((xpm_map_t) cuphead10_110);
        cuphead11 = create_sprite((xpm_map_t) cuphead11_110);
        cuphead12 = create_sprite((xpm_map_t) cuphead12_110);
        cuphead13 = create_sprite((xpm_map_t) cuphead13_110);
        cuphead14 = create_sprite((xpm_map_t) cuphead14_110);
        cuphead15 = create_sprite((xpm_map_t) cuphead15_110);
        cuphead16 = create_sprite((xpm_map_t) cuphead16_110);
        cupheadstand = create_sprite((xpm_map_t) cupheadstand_110);

        hearthLife = create_sprite((xpm_map_t) hearth2_110);
        font = create_sprite((xpm_map_t) PressStart2P_vaV7_110);
        ScoreBackGrnd = create_sprite((xpm_map_t) ScoreBoardBackgrd_110);
        LeaderBackGrnd = create_sprite((xpm_map_t) LeaderboardMenu_110);
        mouse_cursor= create_sprite((xpm_map_t) square_110);
        menu_full = create_sprite((xpm_map_t) full_Menu_110);
        background = create_sprite((xpm_map_t) background_110);
        monster1 = create_sprite((xpm_map_t) monster1_110);
        monster2 = create_sprite((xpm_map_t) monster2_110);
        bala = create_sprite((xpm_map_t) bala_110);
    }
    
}

int clean_img(uint16_t x, uint16_t y, uint16_t width) {
    for (int w = 0 ; w < width ; w++) {
        for (int h = 0 ; h < width ; h++) {
            if (vg_draw_pixel(x + w, y + h, 0)) return 1;
        }
    }
    return 0; 
}
/*
void freeAllSprites(){

}
*/

bool check_collision(Sprite *sp1, int x1, int y1, Sprite *sp2, int x2,  int y2) {
    if (sp1 == NULL || sp2 == NULL) return false;

    int sp1_x_end = x1 + sp1->width;
    int sp1_y_end = y1 + sp1->height;
    int sp2_x_end = x2 + sp2->width;
    int sp2_y_end = y2 + sp2->height;
    
    if ((x1 < sp2_x_end && sp1_x_end > x2) && (y1 < sp2_y_end && sp1_y_end > y2)) {
        return true;
    }
    return false;
    
}

int drawChar(char c, uint16_t x, uint16_t y) { //height = 17, width = 16 on 0x14C mode
    uint16_t xMap, yMap;
    switch (c)
    {
    case 'a':
        xMap =9; 
        yMap =1;
        break;
    case 'b':
        xMap =9+18; 
        yMap =1;
        break;
    case 'c':
        xMap =9+2*18; 
        yMap =1;
        break;
    case 'd':
        xMap =9+3*18; 
        yMap =1;
        break;
    case 'e':
        xMap =9+4*18; 
        yMap =1;
        break;
    case 'f':
        xMap =9+5*18; 
        yMap =1;
        break;
    case 'g':
        xMap =9+6*18; 
        yMap =1;
        break;
    case 'h':
        xMap =9+7*18; 
        yMap =1;
        break;
    case 'i':
        xMap =9+8*18; 
        yMap =1;
        break;
    case 'j':
        xMap =9+9*18; 
        yMap =1;
        break;
    case 'k':
        xMap =9+10*18; 
        yMap =1;
        break;
    case 'l':
        xMap =9+11*18; 
        yMap =1;
        break;
    case 'm':
        xMap =9+12*18; 
        yMap =1;
        break;
    case 'n':
        xMap =9+13*18; 
        yMap =1;
        break;
    case 'o':
        xMap =9+14*18; 
        yMap =1;
        break;
    case 'p':
        xMap =9+15*18; 
        yMap =1;
        break;
    case 'q':
        xMap =9+16*18; 
        yMap =1;
        break;
    case 'r':
        xMap =9+17*18; 
        yMap =1;
        break;
    case 's':
        xMap =9+18*18; 
        yMap =1;
        break;
    case 't':
        xMap =9+19*18; 
        yMap =1;
        break;
    case 'u':
        xMap =9+20*18; 
        yMap =1;
        break;
    case 'v':
        xMap =9+21*18; 
        yMap =1;
        break;
    case 'w':
        xMap =9+22*18; 
        yMap =1;
        break;
    case 'x':
        xMap =9+23*18; 
        yMap =1;
        break;
    case 'y':
        xMap =9+24*18; 
        yMap =1;
        break;
    case 'z':
        xMap =9+25*18; 
        yMap =1;
        break;
    case ':':
        xMap =9+11*18; 
        yMap =36; 
        break;

    case '0':
        xMap =9; 
        yMap =36;
        break;
    case '1':
        xMap =9+18; 
        yMap =36;
        break;
    case '2':
        xMap =9+2*18; 
        yMap =36;
        break;
    case '3':
        xMap =9+3*18; 
        yMap =36;
        break;
    case '4':
        xMap =9+4*18; 
        yMap =36;
        break;
    case '5':
        xMap =9+5*18; 
        yMap =36;
        break;
    case '6':
        xMap =9+6*18; 
        yMap =36;
        break;
    case '7':
        xMap =9+7*18; 
        yMap =36;
        break;
    case '8':
        xMap =9+8*18; 
        yMap =36;
        break;
    case '9':
        xMap =9+9*18; 
        yMap =36;
        break;
    case '/':
        xMap =9+30*18; 
        yMap =36;
        break;
    case '-':
        xMap =9+27*18; 
        yMap =36;
        break;
    
   
    default:
        break;
    }
    for (int h = 0 ; h < 18; h++) {
        for (int w = 0 ; w < 18; w++) {
            if (vg_draw_pixel(x + w,y + h, font->map[xMap*info.XResolution/1152 + w + (yMap*info.YResolution/864+h)*800])) return 1;
        }
    }
    return 0;
}

int drawNum(int c, uint16_t x, uint16_t y) { //height = 17, width = 16
    uint16_t xMap, yMap;
    switch (c)
    {
    case 0:
        xMap =9; 
        yMap =36;
        break;
    case 1:
        xMap =9+18; 
        yMap =36;
        break;
    case 2:
        xMap =9+2*18; 
        yMap =36;
        break;
    case 3:
        xMap =9+3*18; 
        yMap =36;
        break;
    case 4:
        xMap =9+4*18; 
        yMap =36;
        break;
    case 5:
        xMap =9+5*18; 
        yMap =36;
        break;
    case 6:
        xMap =9+6*18; 
        yMap =36;
        break;
    case 7:
        xMap =9+7*18; 
        yMap =36;
        break;
    case 8:
        xMap =9+8*18; 
        yMap =36;
        break;
    case 9:
        xMap =9+9*18; 
        yMap =36;
        break;
    
    default:
        return 1;
    }
    for (int h = 0 ; h < 18; h++) {
        for (int w = 0 ; w < 18; w++) {
            if (vg_draw_pixel(x + w,y + h, font->map[xMap*info.XResolution/1152 + w + (yMap*info.YResolution/864+h)*800])) return 1;
        }
    }
    return 0;
}

int drawTxt(char txt[], uint16_t x, uint16_t y) {
    uint8_t i=0;
    while(txt[i]) {
        if(txt[i]==' ') {
            i++;
        }
        else {
            if(drawChar(txt[i],x+(18)*i,y)) {return 1;}
            i++;
        }   
    }
    return 0;
}

