#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <lcom/lcf.h>
#include <stdint.h>


int (set_graphic_mode)(uint16_t submode);
int (set_buffer)(uint16_t mode);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (draw_xpm)(xpm_map_t xmap, uint16_t x, uint16_t y);
void (fix_color)(uint32_t color, uint32_t *new_color);

int(allocate_write_buffer)();
void(switch_buffers)();


#endif
