#include "structs.h"
#include "gameViewer.h"
#include "gameController.h"



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


void gameLoop() {
    while (1) {
        if(keyboard_subscribe_int(&hook_id_kbd) != 0) 
            return;
        if(mouse_subscribe_int(&hook_id_mouse) != 0)
            return;
        if(timer_subscribe_int(&hook_id_timer) != 0)
            return;
        /*
        if(rtc_subscribe_int(&hook_id_rtc) != 0)
            return;
        if(graphics_subscribe_int(&hook_id_graphics) != 0)
            return;
        */

        updateGameState();
        renderGameState();


        if(keyboard_unsubscribe_int() != 0)
            return;
        if(mouse_unsubscribe_int() != 0)
            return;
        if(timer_unsubscribe_int() != 0)
            return;
        
        
        /*
        if(rtc_unsubscribe_int() != 0)
            return;
        if(graphics_unsubscribe_int() != 0)
            return;
        */
    }
}

int main() {
    gameLoop();
    return 0;
}
