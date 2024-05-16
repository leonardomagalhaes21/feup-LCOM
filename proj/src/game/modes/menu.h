


#ifndef __MENU_H
#define __MENU_H
#include <lcom/lcf.h>
#include "../../devices/mouse/mouse.h"
#include "../../devices/keyboard/keyboard.h"
#include "../../devices/graphics/graphics.h"

#include "../sprite/sprite.h"
#include "../classes/player.h"

typedef enum {
  MENU,
  GAME,
  PAUSE,
  SCOREBOARD,
  LEADERBOARD,
  EXIT,
} GameState;
extern GameState currentState;

void setMenuState();
int playButton(int x, int y);
int leaderboardButton(int x, int y);
int exitButton(int x, int y);
int drawMenu();
int drawGame(player *player);
#endif

