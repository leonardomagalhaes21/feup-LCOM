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
#include "game/classes/enemy.h"

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

uint8_t kbd_irq_set;
uint8_t mouse_irq_set;
uint8_t timer_irq_set;
uint16_t mode = 0x14C;

int open_devices(){
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
  return 0;
}


int close_devices() {
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


int(proj_main_loop)(int argc, char *argv[]) {

  loadAllSprites();
  int ipc_status;
  message msg;

  int8_t speed_x = 0;
  int8_t speed_y = 0;


  int cuphead_offset = 1;
  


  if(open_devices()!=0)
    return 1;
  
  player *player;
  player = createPlayer(5, 5, 400, 571, cuphead1);
  MouseCursor *mouse;
  mouse = createMouseCursor(400,350, mouse_cursor);
  //enemy monsters[10];
  
bool key_a_pressed = false;
bool key_d_pressed = false; 
bool key_w_pressed = false;
bool create_enemy=false;
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
                        drawGame();
                        if (cuphead_offset == 0){
                          player->sprite = cuphead1;
                          cuphead_offset++;
                        }
                        
                        else if (cuphead_offset == 1){
                          player->sprite = cuphead2;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 2){
                          player->sprite = cuphead3;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 3){
                          player->sprite = cuphead4;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 4){
                          player->sprite = cuphead5;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 5){
                          player->sprite = cuphead6;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 6){
                          player->sprite = cuphead7;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 7){
                          player->sprite = cuphead8;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 8){
                          player->sprite = cuphead9;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 9){
                          player->sprite = cuphead10;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 10){
                          player->sprite = cuphead11;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 11){
                          player->sprite = cuphead12;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 12){
                          player->sprite = cuphead13;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 13){
                          player->sprite = cuphead14;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 14){
                          player->sprite = cuphead15;
                          cuphead_offset++;
                        }
                        else if (cuphead_offset == 15){
                          player->sprite = cuphead16;
                          cuphead_offset = 0;
                        }
                        update_player_logic(player, mouse, key_a_pressed, key_d_pressed, key_w_pressed,&speed_x,&speed_y);
                        if(counter_timer % 300 == 0){
                          create_enemy=true;
                        }
                      //update_enemy_logic(mouse,monsters,create_enemy);
                      create_enemy=false;
                    }
                    else if(currentState ==LEADERBOARD){
                      drawGame();
                    }
                    else if(currentState ==EXIT){
                      if(close_devices()!=0)
                        return 1;
                      return 0;
                    }
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
                            exitButton(mouse->x, mouse->y);
                        }
                    }
                }
                break;
                
            default:
                break;
        }
    }
}

  if(close_devices()!=0)
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
