#include "menu.h"

extern uint8_t scancode;
extern struct packet mouse_packet;
GameState currentState = MENU; 

char name[10];
uint8_t indexName=0;

int processScanCode(uint8_t scancode) {
  if(indexName<10) {
  if (scancode == 0x1E) { // a
    name[indexName] = 'a';
    indexName++;
  }
  else if (scancode == 0x30) { // b
    name[indexName] = 'b';
    indexName++;
  }
  else if (scancode == 0x2E) { // c
    name[indexName] = 'c';
    indexName++;
  }
  else if (scancode == 0x20) { // d
    name[indexName] = 'd';
    indexName++;
  }
  else if (scancode == 0x12) { // e
    name[indexName] = 'e';
    indexName++;
  }
  else if (scancode == 0x21) { // f
    name[indexName] = 'f';
    indexName++;
  }
  else if (scancode == 0x22) { // g
    name[indexName] = 'g';
    indexName++;
  }
  else if (scancode == 0x23) { // h
    name[indexName] = 'h';
    indexName++;
  }
  else if (scancode == 0x17) { // i
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
int menuButton(int x, int y, int *score, double *multiplier){
    if(335 < x && 800> x && 455 < y && 600 > y){
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
    int numberOfScores = 7;
    char names[numberOfScores][10];
    char dates[numberOfScores][18];
    int scores[numberOfScores];
    
    for (int i = 0; i < numberOfScores; i++) {
        strcpy(names[i], "default");
    }
    read_scores(names,scores, dates,numberOfScores);
    for(int i = 0; i< numberOfScores;i++) {
      if (strcmp(names[i], "default") == 0) {
          return 0;
      }
      drawTxt(names[i],270,260+30*i);
      drawTxt(dates[i],270+18*10,260+30*i);
      drawScore(scores[i],850,260+30*i);
    }
    
    return 0;
}

int menuButtonLeader(int x, int y) {
  if(270 < x && 890> x &&  600 < y && 740 > y){
        if(mouse_packet.lb)
            currentState = MENU;
        }
    
    return 0;
}

int drawGame(player *player, int score){

    
   draw_sprite(background, 0, 0);
    uint16_t xpos=5;
    for(uint8_t i = 0; i<player->life;i++) {
        draw_sprite(hearthLife, xpos,5);
        xpos+=25;
    }
    drawScore(score, 1100, 38);
    
    return 0;
}

int drawScoreBoard(int score) {
    if(draw_sprite(ScoreBackGrnd, 0, 0)) {return 1;}
    if(drawTxt("your score:", 470, 290)) {return 1;}
    if(drawScore(score, 585, 330)) {return 1;}
    if(drawTxt("name:", 470, 360)) {return 1;}
    //processScanCode(scancode);
    if(drawTxt(name,470+6*18, 360)) {return 1;}
    return 0;
}

int drawScore(int score, uint16_t x, uint16_t y) {   
    uint16_t pos=0;
    while (score>0) {
        uint8_t rem = score%10;
        if(drawNum(rem, x-pos*21,y)) {return 1;} //escreve da direita para a esquerda
        pos++;
        score = score / 10;
    }
    
    
    return 0;
}

