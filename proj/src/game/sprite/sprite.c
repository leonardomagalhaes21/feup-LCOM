/** Creates a new sprite from XPM "pic", with specified
* position (within the screen limits) and speed;
* Does not draw the sprite on the screen
* Returns NULL on invalid pixmap.
*/

#include <lcom/lcf.h>
#include "sprite.h"





Sprite *create_sprite(xpm_map_t pic) {
    //allocate space for the "object"
    Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
    xpm_image_t img;
    
    if( sp == NULL )
    return NULL;
    // read the sprite pixmap
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
    sp = NULL; // XXX: pointer is passed by value
    // should do this @ the caller
}
// XXX: move_sprite would be a more appropriate name
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
void loadAllSprites(){
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

    mouse_cursor= create_sprite((xpm_map_t) square);
    menu_full = create_sprite((xpm_map_t) full_Menu);
    background = create_sprite((xpm_map_t) back_ground);
    monster1 = create_sprite((xpm_map_t) monster_1);
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

static int check_collision(Sprite *sp1, int x1, int y1, Sprite *sp2, int x2, int y2)
{
    return 1;
}*/
