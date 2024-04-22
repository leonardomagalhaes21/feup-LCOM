#include "game/structs.h"
#include "game/viewer/gameViewer.h"
#include "game/controller/gameController.h"
#include "devices/graphics/graphics.h"
#include "devices/keyboard/keyboard.h"
#include "devices/mouse/mouse.h"
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


int (proj_main_loop)(int argc, char *argv[]) {


     int ipc_status;
    message msg;

    uint8_t kbd_irq_set;
    uint8_t mouse_irq_set;
    uint8_t timer_irq_set;

    uint16_t submode = 0x105;
    if(keyboard_subscribe_int(&kbd_irq_set) != 0) 
        return 1;
    if(mouse_subscribe_int(&mouse_irq_set) != 0)
        return 1;
    if(timer_subscribe_int(&timer_irq_set) != 0)
        return 1;
    if(set_graphic_mode(submode) != 0)
        return 1;



    while (scancode != ESC_BREAKCODE){
        if (driver_receive(ANY, &msg, &ipc_status) != 0) { 
        printf("driver_receive failed");
        continue;
        }
        if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: 
            if (msg.m_notify.interrupts & kbd_irq_set) {
                kbc_ih();
                break;
            }
            default:
                break; 
        }
        }
    }

    if(keyboard_unsubscribe_int() != 0)
        return 1;
    if(mouse_unsubscribe_int() != 0)
        return 1;
    if(timer_unsubscribe_int() != 0)
        return 1;
    
    
    /*
    if(rtc_unsubscribe_int() != 0)
        return;
    */
    if(vg_exit() != 0)
        return 1;
    
    return 0;
}

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
    //lcf_trace_calls("/home/lcom/labs/proj/src/main.c");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

