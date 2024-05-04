#include "animsprite.h"
#include <lcom/lcf.h>
#include <stdarg.h>
#include <stdint.h>

AnimSprite *create_animSprite(uint8_t no_pic, int animspritespeed, char *pic1[], ...) {
    AnimSprite *asp = malloc(sizeof(AnimSprite));
    
    asp->sp = create_sprite(pic1, 0, 0, 0, 0);
    
    asp->map = malloc(no_pic * sizeof(char *));
    
    asp->map[0] = asp->sp->map;

    va_list ap;
    va_start(ap, pic1);
    for (unsigned i = 1; i < no_pic; i++) {
        char **tmp = va_arg(ap, char **);
        xpm_image_t img;
        asp->map[i] = xpm_load(tmp, XPM_INDEXED, &img);
        if (asp->map[i] == NULL || img.width != asp->sp->width || img.height != asp->sp->height) {
            for (unsigned j = 1; j < i; j++)
                free(asp->map[j]);
            free(asp->map);
            destroy_sprite(asp->sp);
            free(asp);
            va_end(ap);
            return NULL;
        }
    }
    va_end(ap);

    asp->aspeed = animspritespeed; 
    asp->cur_aspeed = animspritespeed;
    asp->num_fig = no_pic;
    asp->cur_fig = 1;

    return asp;
}

int animate_animSprite(AnimSprite *asp) {
    if (asp == NULL) {
        return -1;
    }
    if(asp->cur_aspeed==0) {
        asp->cur_aspeed = asp->aspeed;
        if(asp->cur_fig==asp->num_fig) {
            asp->cur_fig = 1;
        } else {asp->cur_fig++;}
    }

    asp->cur_aspeed--;

    asp->sp = asp->map[asp->cur_fig];
    
    return 0;
}

void destroy_anim_sprite(AnimSprite *asp) {
    if (asp == NULL)
        return;

    if (asp->sp != NULL)
        destroy_sprite(asp->sp);

    if (asp->map != NULL) {
        for (int i = 0; i < asp->num_fig; i++) {
            if (asp->map[i] != NULL)
                free(asp->map[i]);
        }
        free(asp->map);
    }

    free(asp);
    asp = NULL; 
}
    
    