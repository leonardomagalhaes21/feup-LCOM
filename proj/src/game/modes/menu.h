


#ifndef __MENU_H
#define __MENU_H
#include <lcom/lcf.h>
#include "../../devices/mouse/mouse.h"
#include "../../devices/keyboard/keyboard.h"
#include "../../devices/graphics/graphics.h"
#include "game/logic/save_score.h"
#include "../sprite/sprite.h"
#include "../classes/player.h"

typedef enum {
  MENU,
  GAME,
  SCOREBOARD,
  LEADERBOARD,
  EXIT,
  RESOLUTION,
} GameState;
extern GameState currentState;

void setMenuState();
int playButton(int x, int y);
int leaderboardButton(int x, int y);
int exitButton(int x, int y);
int menuButton(int x, int y, int *score, double *multiplier);
int menuButtonLeader(int x, int y);
int drawMenu();
int drawGame(player *player, int score);
int drawScoreBoard(int score);
int drawScore(int score, uint16_t x, uint16_t y);
int processScanCode(uint8_t scancodewrite);
int drawLeaderBoard();
int drawResolution();
int res14C(int x, int y);
int res110(int x, int y);
int res11A(int x, int y);
int res115(int x, int y);

#endif

