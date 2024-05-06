#include "menu.h"

extern struct packet mouse_packet;


int drawMenu(){
    draw_sprite(menu_full, 400, 400);
    return 0;
}
