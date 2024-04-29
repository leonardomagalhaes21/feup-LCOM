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

typedef enum {
  MENU,
  GAME,
  PAUSE,
  SCOREBOARD,
  LEADERBOARD,
} GameState;

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
GameState currentState = MENU;

void changeGameState(GameState newState) {
  currentState = newState;
}

void initGameState() {
  switch (currentState) {
    case MENU:
      changeGameState(MENU);
      break;
    case GAME:
      changeGameState(GAME);
      break;
    case PAUSE:
      changeGameState(PAUSE);
      break;
    case SCOREBOARD:
      changeGameState(SCOREBOARD);
      break;
    case LEADERBOARD:
      changeGameState(LEADERBOARD);
      break;
  }
}

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
  /*
   if(draw_xpm((xpm_map_t) square, 0, 0)!= 0)
      return 1;
  */

  player *player;
  player = createPlayer(5, 5, 200, 0, main_char);
  MouseCursor *mouse;
  mouse = createMouseCursor(400,200, mouse_cursor);

  bool is_falling = true;

  draw_sprite(player->sprite, player->x, player->y);
  draw_sprite(mouse->sprite, mouse->x, mouse->y);

  while (scancode != ESC_BREAKCODE) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("driver_receive failed");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & timer_irq_set) {
            if (is_falling) {
              speed_y += 1;
            }

            player->y += speed_y;
            if (player->y > 300) {
              speed_y = 0;
              is_falling = false;
            }
            player->x += speed_x;
            draw_sprite(player->sprite, player->x, player->y);
            draw_sprite(mouse->sprite, mouse->x, mouse->y);

            switch_buffers();
          }
          if (msg.m_notify.interrupts & kbd_irq_set) {
            kbc_ih();
            if (scancode == 0x1E) { // A
              speed_x = -3;
            }
            else if (scancode == 0x20) { // D
              speed_x = 3;
            }
            else if (scancode == 0x11) { // w
              if (!is_falling) {
                is_falling = true;
                speed_y = -20;
              }
            }
            else if (scancode == 0x1F) { // S
              speed_y = 3;
            }
            else {
              speed_y = 0;
              speed_x = 0;
            }
            break;
          }
          if (msg.m_notify.interrupts & mouse_irq_set) {
            mouse_ih();
            mouse_bytes_sync();

            if (idx == 3) {
              idx = 0;
            mouse_generate_packet();
            
             //if (!((mouse_packet.delta_x +mouse->x) < 0 || (mouse_packet.delta_x +mouse->x) > (info.XResolution) || (mouse_packet.delta_y + mouse->y) < 0 || (mouse_packet.delta_y + mouse->y) > (info.YResolution))){
                clean_img(mouse->x,mouse->y,100);
                mouse->x += mouse_packet.delta_x;
                mouse->y-=mouse_packet.delta_y;
            //}

        
            }
          }
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
