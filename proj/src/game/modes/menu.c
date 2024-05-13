#include "menu.h"

bool menu = true;
bool game = false;
bool leaderboard = false;
extern struct packet mouse_packet;
GameState currentState = MENU; 
void setMenuState(){
    currentState=MENU;
    
}
int playButton(int x, int y){
    if(440 < x && 710> x && 360 < y && 430 > y){
        if(!game){
            if(mouse_packet.lb)
                game = true;
                menu = false;
                leaderboard = false;
        }
        if(game){    
            currentState = GAME;
            game=false;
            
        }
    }
    else 
        game=false;
    return 0;
}
int leaderboardButton(int x, int y){
    if(440 < x && 710> x && 450 < y && 520 > y){
        if(!leaderboard){
            if(mouse_packet.lb)
                leaderboard = true;
                menu = false;
                game = false;
        }
        if(leaderboard){    
            currentState = LEADERBOARD;
            leaderboard=false;
            
        }
    }
    else {
        leaderboard=false;
    }
    return 0;
}

int drawMenu(){
    draw_sprite(menu_full, 0, 0);
    return 0;
}
int drawGame(){
    draw_sprite(background, 0, 0);
    return 0;
}
