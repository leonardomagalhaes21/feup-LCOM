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

int drawGame(player *player, int score){

    
   draw_sprite(background, 0, 0);
    uint16_t xpos=5;
    for(uint8_t i = 0; i<player->life;i++) {
        draw_sprite(hearthLife, xpos,5);
        xpos+=25;
    }
    drawScore(score);
    
    return 0;
}

int drawScore(int score) {   
    uint16_t pos=0;
    while (score>0) {
        uint8_t rem = score%10;
        if(drawNum(rem, 1100-pos*21,38)) {return 1;} //escreve da direita para a esquerda
        pos++;
        score = score / 10;
    }
    
    
    return 0;
}
