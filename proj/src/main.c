#include "devices/graphics/graphics.h"
#include "devices/keyboard/keyboard.h"
#include "devices/mouse/mouse.h"
#include "game/classes/mouse_cursor.h"
#include "game/classes/player.h"
#include "game/classes/structs.h"
#include "game/controller/gameController.h"
#include "game/sprite/sprite.h"
#include "game/viewer/gameViewer.h"
#include "lcom/timer.h"
#include "game/modes/menu.h"
#include "game/logic/game_logic.h"

extern int hook_id_kbd;
extern int hook_id_mouse;
extern int hook_id_timer;
extern int hook_id_rtc;
extern int hook_id_graphics;
extern int counter_timer;
extern uint8_t scancode;
extern uint8_t scancode_mouse;
extern struct packet mouse_packet;
extern int idx;
extern vbe_mode_info_t info;
extern GameState currentState;
//void changeGameState(GameState newState) {
//  GameState currentState = newState;
//}



int(proj_main_loop)(int argc, char *argv[]) {

  loadAllSprites();
  int ipc_status;
  message msg;

  int8_t speed_x = 0;
  int8_t speed_y = 0;

  uint8_t kbd_irq_set;
  uint8_t mouse_irq_set;
  uint8_t timer_irq_set;

  uint16_t mode = 0x14C;


  if (mouse_write_cmd(MOUSE_ENABLE_DATA_REPORTING) != 0)
    return 1;

  if (keyboard_subscribe_int(&kbd_irq_set) != 0)
    return 1;
  if (mouse_subscribe_int(&mouse_irq_set) != 0)
    return 1;


  if (timer_set_frequency(0, 30) != 0)
    return 1;
  if (timer_subscribe_int(&timer_irq_set) != 0)
    return 1;

  if (set_buffer(mode) != 0)
    return 1;

  if (allocate_write_buffer() != 0)
    return 1;

  if (set_graphic_mode(mode) != 0)
    return 1;
  

  player *player;
  player = createPlayer(5, 5, 200, 0, main_char);
  MouseCursor *mouse;
  mouse = createMouseCursor(400,350, mouse_cursor);
  //draw_sprite(menu_full,0,0);

  
  /* botão de play  
  for(int width =440; width < 710; width++){
    for(int height = 360; height < 430; height++){
      vg_draw_pixel(width,height,0x000000);
    }
  }
  */
  /*botão de Leaderboard
  for(int width =440; width < 710; width++){
    for(int height = 450; height < 520; height++){
      vg_draw_pixel(width,height,0x000000);
    }
  }
  */
  /*Botão de exit
  for(int width =440; width < 710; width++){
    for(int height = 540; height < 610; height++){
      vg_draw_pixel(width,height,0x000000);
    }
  }
  */
bool key_a_pressed = false;
bool key_d_pressed = false; 
bool key_w_pressed = false;
//bool is_falling=true;

while (scancode != ESC_BREAKCODE) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
        printf("driver_receive failed");
        continue;
    }
    if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:
                if (msg.m_notify.interrupts & timer_irq_set) {
                    timer_int_handler();
                    
                    if (currentState == MENU) {
                        drawMenu();
                    }
                    else if (currentState == GAME) {
                        update_game_logic(player, mouse, key_a_pressed, key_d_pressed, key_w_pressed,&speed_x,&speed_y);
                        drawGame();
                        draw_sprite(player->sprite, player->x, player->y);
                    }
                    else if(currentState ==LEADERBOARD){
                      drawGame();
                      draw_sprite(monster1,5,5);
                    }
                    
                    /*
                    int8_t speed_x = 0;
                    int8_t speed_y = 0;

                    if (is_falling) {
                        speed_y += 1;
                    }

                    player->y += speed_y;

                    if (player->y > 570) {
                        player->y = 570;
                        speed_y = 0;
                        is_falling = false;
                    }

                    if (key_a_pressed) {
                        speed_x = -3; 
                    } else if (key_d_pressed) {
                        speed_x = 3; 
                    } else {
                        speed_x = 0; 
                    }
                    player->x += speed_x;

                    if (key_w_pressed && !is_falling) {
                        is_falling = true;
                        speed_y = -20;
                    }

                    */
                    
                    
                    draw_sprite(mouse->sprite, mouse->x, mouse->y);
                    
                    switch_buffers();
                }
                
                if (msg.m_notify.interrupts & kbd_irq_set) {
                    kbc_ih();
                    
                    if (scancode == 0x1E) {
                        key_a_pressed = true;
                    } else if (scancode == 0x9E) {
                        key_a_pressed = false;
                    } else if (scancode == 0x20) {
                        key_d_pressed = true;
                    } else if (scancode == 0xA0) {
                        key_d_pressed = false;
                    } else if (scancode == 0x11) {
                        key_w_pressed = true;
                    } else if (scancode == 0x91) {
                        key_w_pressed = false;
                    }
                }
                
                if (msg.m_notify.interrupts & mouse_irq_set) {
                    mouse_ih();
                    mouse_bytes_sync();

                    if (idx == 3) {
                        idx = 0;
                        mouse_generate_packet();
                        if (!((mouse_packet.delta_x + mouse->x) <= 0 || (mouse_packet.delta_x + mouse->x + 7) >= (info.XResolution) || (-mouse_packet.delta_y + mouse->y) <= 0 || (-mouse_packet.delta_y + mouse->y) > (info.YResolution))) {
                            mouse->x += mouse_packet.delta_x;
                            mouse->y -= mouse_packet.delta_y;
                        }
                        if (currentState == MENU) {
                            playButton(mouse->x, mouse->y);
                            leaderboardButton(mouse->x, mouse->y);
                        }
                    }
                }
                break;
                
            default:
                break;
        }
    }
}





  if (keyboard_unsubscribe_int() != 0)
    return 1;
  if (mouse_unsubscribe_int() != 0)
    return 1;
  if (mouse_write_cmd(0xF5) != 0)
    return 1;
  if (timer_unsubscribe_int() != 0)
    return 1;

  /*
  if(rtc_unsubscribe_int() != 0)
      return;
  */
  if (vg_exit() != 0)
    return 1;

  return 0;
}

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");
  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
