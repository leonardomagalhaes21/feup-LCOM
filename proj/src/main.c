#include "devices/graphics/graphics.h"
#include "devices/keyboard/keyboard.h"
#include "devices/mouse/mouse.h"
#include "game/classes/enemy.h"
#include "game/classes/mouse_cursor.h"
#include "game/classes/player.h"
#include "game/controller/gameController.h"
#include "game/logic/game_logic.h"
#include "game/modes/menu.h"
#include "game/sprite/sprite.h"
#include "game/viewer/gameViewer.h"
#include "lcom/timer.h"
#include "game/classes/bullet.h"
#include "game/classes/bullet_node.h"





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
extern int renew;
int score=0;
double multiplier = 1.0;


uint8_t kbd_irq_set;
uint8_t mouse_irq_set;
uint8_t timer_irq_set;
uint16_t mode = 0x14C;

int open_devices() {
  if (mouse_write_cmd(0xEA) != 0)
    return 1;
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

  loadAllSprites(mode);
  int ipc_status;
  message msg;

  int8_t speed_x = 0;
  int8_t speed_y = 0;

  if (open_devices() != 0)
    return 1;

  player *player;
  player = createPlayer(5, 5, 400*info.XResolution/1152, 571*info.YResolution/864, cuphead1);
  MouseCursor *mouse;
  mouse = createMouseCursor(400*info.XResolution/1152, 350*info.YResolution/864, mouse_cursor);
  bullet_node *bullets = NULL;
  extern enemy monsters[10];
  int v = 10;
  for (int i = 0; i < 10; i++) {
    monsters[i] = *createEnemy(5, 5, 5 + i + v, 5 + i + v, 3, 3, monster1, false);
  }

  extern enemy monsters_fly[2];
    monsters_fly[0] = *createEnemy(6, 5, FLYMONS1_X, FLYMONS1_Y, 3, 3, monster2, true);

    monsters_fly[1] = *createEnemy(6,5, FLYMONS2_X, FLYMONS2_Y, 3, 3, monster2, true);

  int bullet_cooldown=0;
  bool key_a_pressed = false;
  bool key_d_pressed = false;
  bool key_w_pressed = false;
  bool create_enemy = false;
  int unvulnerability = 0;
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

              unvulnerability++;
              bullet_cooldown++;
              

              drawGame(player, score);

              update_bullet_logic(&bullets);


              update_player_logic(player, mouse, key_a_pressed, key_d_pressed, key_w_pressed, &speed_x, &speed_y, &unvulnerability);
              
              if (counter_timer % 60 == 0) {
                create_enemy = true;
                renew+=1;
              }
              if(renew>=5){
                spawn_dead_enemies();
                renew=0;
              }
              if (currentState == GAME) {
                if (counter_timer % 60 == 0) {
                  multiplier+=0.1;
                }
                if(counter_timer%20 == 0) {
                  score+=10*multiplier;
                }
              }
              
              update_enemy_logic(mouse, create_enemy,player);
              create_enemy = false;
            }
            else if (currentState == LEADERBOARD) {
              drawLeaderBoard();
            }
            else if (currentState == SCOREBOARD) {
              drawScoreBoard(score);
            }
            else if (currentState == EXIT) {
              if (close_devices() != 0)
                return 1;
              return 0;
            }
            draw_sprite(mouse->sprite, mouse->x, mouse->y);

            switch_buffers();
            
          }

          if (msg.m_notify.interrupts & kbd_irq_set) {
            kbc_ih();
            if (currentState == SCOREBOARD) {
              processScanCode(scancode);
            }
            if (scancode == 0x1E) {
              key_a_pressed = true;
            }
            else if (scancode == 0x9E) {
              key_a_pressed = false;
            }
            else if (scancode == 0x20) {
              key_d_pressed = true;
            }
            else if (scancode == 0xA0) {
              key_d_pressed = false;
            }
            else if (scancode == 0x11) {
              key_w_pressed = true;
            }
            else if (scancode == 0x91) {
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
              if (currentState == LEADERBOARD) {
                menuButtonLeader(mouse->x, mouse->y);
                
              }
              if (currentState == SCOREBOARD) {
                menuButton(mouse->x, mouse->y, &score, &multiplier);
                
              }
              else if(currentState == GAME){
                if (mouse_packet.lb) {
                  if(bullet_cooldown > 30){
                    bullet_cooldown = 0;
                
                    bullet *new_shot = createBullet(player->x+75, player->y+50, mouse->x, mouse->y, 3, bala);
                    addBullet(&bullets, new_shot);
                  }
                }
              }
            }
          }
          break;

        default:
          break;
      }
    }
  }

  if (close_devices() != 0)
    return 1;
  return 0;
}

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  //lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");
  //lcf_log_output("/home/lcom/labs/proj/src/output.txt");
  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
