#include "menu.h"
#include "game/logic/game_logic.h"
extern uint8_t scancode;
extern struct packet mouse_packet;
char names[7][10];
int scores[7];
char dates[7][18];
GameState currentState = RESOLUTION; 
extern vbe_mode_info_t info;
extern enemy monsters_fly[2];
extern uint16_t mode;


char name[10];
uint8_t indexName=0;

int processScanCode(uint8_t scancode) {
  if(indexName<10) {
  if (scancode == 0x1E) { 
    name[indexName] = 'a';
    indexName++;
  }
  else if (scancode == 0x30) { 
    name[indexName] = 'b';
    indexName++;
  }
  else if (scancode == 0x2E) { 
    name[indexName] = 'c';
    indexName++;
  }
  else if (scancode == 0x20) { 
    name[indexName] = 'd';
    indexName++;
  }
  else if (scancode == 0x12) { 
    name[indexName] = 'e';
    indexName++;
  }
  else if (scancode == 0x21) { 
    name[indexName] = 'f';
    indexName++;
  }
  else if (scancode == 0x22) { 
    name[indexName] = 'g';
    indexName++;
  }
  else if (scancode == 0x23) { 
    name[indexName] = 'h';
    indexName++;
  }
  else if (scancode == 0x17) { 
    name[indexName] = 'i';
    indexName++;
  }
  else if (scancode == 0x24) {
    name[indexName] = 'j';
    indexName++;
  }
  else if (scancode == 0x25) {
    name[indexName] = 'k';
    indexName++;
  }
  else if (scancode == 0x26) {
    name[indexName] = 'l';
    indexName++;
  }
  else if (scancode == 0x32) {
    name[indexName] = 'm';
    indexName++;
  }
  else if (scancode == 0x31) {
    name[indexName] = 'n';
    indexName++;
  }
  else if (scancode == 0x18) {
    name[indexName] = 'o';
    indexName++;
  }
  else if (scancode == 0x19) {
    name[indexName] = 'p';
    indexName++;
  }
  else if (scancode == 0x10) {
    name[indexName] = 'q';
    indexName++;
  }
  else if (scancode == 0x13) {
    name[indexName] = 'r';
    indexName++;
  }
  else if (scancode == 0x1F) {
    name[indexName] = 's';
    indexName++;
  }
  else if (scancode == 0x14) {
    name[indexName] = 't';
    indexName++;
  }
  else if (scancode == 0x16) {
    name[indexName] = 'u';
    indexName++;
  }
  else if (scancode == 0x2F) {
    name[indexName] = 'v';
    indexName++;
  }
  else if (scancode == 0x11) {
    name[indexName] = 'w';
    indexName++;
  }
  else if (scancode == 0x2D) {
    name[indexName] = 'x';
    indexName++;
  }
  else if (scancode == 0x15) {
    name[indexName] = 'y';
    indexName++;
  }
  else if (scancode == 0x2C) {
    name[indexName] = 'z';
    indexName++;
  }
  else if (scancode == 0x39) {
    name[indexName] = ' '; 
    indexName++;
    }
    else if (scancode == 0x27) {
        name[indexName] = ':'; 
        indexName++;
    }
  }
  if (scancode == 0x0E) {
    if(indexName>0)
        indexName--;
    name[indexName] = '\0';
  }
  return 0;
}

void setMenuState(){
    currentState=MENU;
    
}
int playButton(int x, int y){
    if(440*info.XResolution/1152 < x && 710*info.XResolution/1152> x && 360*info.YResolution/864 < y && 430*info.YResolution/864 > y){
        if(mouse_packet.lb){
            currentState = GAME;
            monsters_fly[0] = *createEnemy(6, 5, FLYMONS1_X*info.XResolution/1152, FLYMONS1_Y*info.YResolution/864, 3, 3, monster2, true);
            monsters_fly[1] = *createEnemy(6,5, FLYMONS2_X*info.XResolution/1152, FLYMONS2_Y*info.YResolution/864, 3, 3, monster2, true);
        }
    }
    return 0;
}
int leaderboardButton(int x, int y){
    if(440*info.XResolution/1152 < x && 710*info.XResolution/1152> x && 450*info.YResolution/864 < y && 520*info.YResolution/864 > y){
        if(mouse_packet.lb){
            read_scores(names,scores, dates,7);
            currentState = LEADERBOARD;
        }
        }
    return 0;
}
int exitButton(int x, int y){
    if(440*info.XResolution/1152 < x && 710*info.XResolution/1152> x && 540*info.YResolution/864 < y && 610*info.YResolution/864 > y){
        if(mouse_packet.lb)
            currentState = EXIT;
        }
    return 0;
}
int menuButton(int x, int y, int *score, double *multiplier){
    if(335*info.XResolution/1152 < x && 800*info.XResolution/1152> x && 455*info.YResolution/864 < y && 600*info.YResolution/864 > y){
        if(mouse_packet.lb) {
          currentState = MENU;
            save_name_score(name, *score);
            *score=0;
            *multiplier=1.1;
        }
            
        }
    
    return 0;
}

int drawMenu(){
    draw_sprite(menu_full, 0, 0);
    return 0;
}

int drawLeaderBoard(){
    draw_sprite(LeaderBackGrnd, 0, 0);
    //int numberOfScores = 7;
    //char names[numberOfScores][10];
    //char dates[numberOfScores][18];
    //int scores[numberOfScores];
    
   
    
    for(int i = 0; i< 7;i++) {
      if (strcmp(names[i], "default") == 0) {
          return 0;
      }
      drawTxt(names[i],270*info.XResolution/1152,(260+30*i)*info.YResolution/864);
      drawTxt(dates[i],(270+18*10)*info.XResolution/1152,(260+30*i)*info.YResolution/864);
      drawScore(scores[i],850*info.XResolution/1152,(260+30*i)*info.YResolution/864);
    }
    
    return 0;
}

int menuButtonLeader(int x, int y) {
  if(270*info.XResolution/1152 < x && 890*info.XResolution/1152> x &&  600*info.YResolution/864 < y && 740*info.YResolution/864 > y){
        if(mouse_packet.lb)
            currentState = MENU;
        }
    
    return 0;
}

int drawGame(player *player, int score){

    
   draw_sprite(background, 0, 0);
    uint16_t xpos=5;
    for(uint8_t i = 0; i<player->life;i++) {
        draw_sprite(hearthLife, xpos*info.XResolution/1152,5*info.YResolution/864);
        xpos+=25;
    }
    drawScore(score, 1100*info.XResolution/1152, 38*info.YResolution/864);
    
    return 0;
}

int drawScoreBoard(int score) {
    if(draw_sprite(ScoreBackGrnd, 0, 0)) {return 1;}
    if(drawTxt("your score:", 470*info.XResolution/1152, 290*info.YResolution/864)) {return 1;}
    if(drawScore(score, 585*info.XResolution/1152, 330*info.YResolution/864)) {return 1;}
    if(drawTxt("name:", 470*info.XResolution/1152, 360*info.YResolution/864)) {return 1;}
    if(drawTxt(name,(470+6*18)*info.XResolution/1152, 360*info.YResolution/864)) {return 1;}
    return 0;
}

int drawScore(int score, uint16_t x, uint16_t y) {   
    uint16_t pos=0;
    int widthLetters=0;
    if(mode == 0x11A) {
        widthLetters=20;
    } else if (mode == 0x110) {
        widthLetters=10;
    } else if (mode == 0x14C){
        widthLetters = 18;
    } else if (mode == 0x115){
        widthLetters=12;
    }
    while (score>0) {
        uint8_t rem = score%10;
        if(drawNum(rem, x-pos*widthLetters,y)) {return 1;} 
        pos++;
        score = score / 10;
    }
    
    
    return 0;
}
int drawResolution(){
  draw_sprite(ResChooseBckgrd, 0, 0);
  return 0;
}


int res14C(int x, int y){
    if(60 < x && 250> x && 130 < y && 210 > y){
        if(mouse_packet.lb){
          currentState = MENU;
          return 0;
        }
    }
    else{
      return 1;
    }
    return 1;
}
int res110(int x, int y){
    if(60 < x && 250> x && 270 < y && 350 > y){
        if(mouse_packet.lb){
          currentState = MENU;
          return 0;
        }
    }
    else{
      return 1;
    }
    return 1;
}
int res11A(int x, int y){
    if(390 < x && 580> x && 270 < y && 350 > y){
        if(mouse_packet.lb){
          currentState = MENU;
          return 0;
        }
    }
    else{
      return 1;
    }
    return 1;
}
int res115(int x, int y){
    if(390 < x && 580> x && 130 < y && 210 > y){
        if(mouse_packet.lb){
            currentState = MENU;
          return 0;
        }
    }
    else{
      return 1;
    }
    return 1;
}
