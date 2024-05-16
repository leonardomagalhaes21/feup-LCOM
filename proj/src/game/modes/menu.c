#include "menu.h"

extern struct packet mouse_packet;
GameState currentState = MENU; 
void setMenuState(){
    currentState=MENU;
    
}
int playButton(int x, int y){
    if(440 < x && 710> x && 360 < y && 430 > y){
        if(mouse_packet.lb){
            currentState = GAME;
        }
    }
    return 0;
}
int leaderboardButton(int x, int y){
    if(440 < x && 710> x && 450 < y && 520 > y){
        if(mouse_packet.lb)
            currentState = LEADERBOARD;
        }
    return 0;
}
int exitButton(int x, int y){
    if(440 < x && 710> x && 540 < y && 610 > y){
        if(mouse_packet.lb)
            currentState = EXIT;
        }
    return 0;
}

int drawMenu(){
    draw_sprite(menu_full, 0, 0);
    return 0;
}
int drawGame(player *player){
    draw_sprite(hearthLife, 5,5);
    draw_sprite(background, 0, 0);
    return 0;
}
