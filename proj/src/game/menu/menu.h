


#ifndef __MENU_H
#define __MENU_H
#include <lcom/lcf.h>
#include "../../devices/mouse/mouse.h"
#include "../../devices/keyboard/keyboard.h"
#include "../../devices/graphics/graphics.h"
#include "game/logic/save_score.h"
#include "../sprite/sprite.h"
#include "../classes/player.h"


/**
 * @brief Enumerates the possible states of the game.
 * 
 * Represents the different states the game can be in, such as the main menu, the game itself, the scoreboard, the leaderboard, or the exit screen.
 */

typedef enum {
  MENU,
  GAME,
  SCOREBOARD,
  LEADERBOARD,
  EXIT,
  RESOLUTION,
} GameState;
extern GameState currentState;


/**
 * @brief Sets the game state to the main menu.
 */
void setMenuState();

/**
 * @brief Handles button click events for the "Play" button in the menu.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int playButton(int x, int y);


/**
 * @brief Handles button click events for the "Leaderboard" button in the menu.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int leaderboardButton(int x, int y);


/**
 * @brief Handles button click events for the "Exit" button in the menu.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int exitButton(int x, int y);


/**
 * @brief Handles button click events for the "Menu" button in the game.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @param score Pointer to the player's score.
 * @param multiplier Pointer to the player's score multiplier.
 * @return int Returns 0 on success.
 */
int menuButton(int x, int y, int *score, double *multiplier);


/**
 * @brief Handles button click events for the "Leaderboard" button in the game.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int menuButtonLeader(int x, int y);


/**
 * @brief Draws the main menu screen.
 * 
 * @return int Returns 0 on success.
 */
int drawMenu();


/**
 * @brief Draws the game over screen.
 * 
 * @param player Pointer to the player structure.
 * @param score The player's final score.
 * @return int Returns 0 on success.
 */
int drawGame(player *player, int score);


/**
 * @brief Draws the scoreboard screen.
 * 
 * @param score The player's score.
 * @return int Returns 0 on success.
 */
int drawScoreBoard(int score);


/**
 * @brief Draws the player's score.
 * 
 * @param score The player's score.
 * @param x The x-coordinate of the score.
 * @param y The y-coordinate of the score.
 * @return int Returns 0 on success.
 */
int drawScore(int score, uint16_t x, uint16_t y);


/**
 * @brief Draws the leaderboard screen.
 * 
 * @return int Returns 0 on success.
 */
int processScanCode(uint8_t scancodewrite);


/**
 * @brief Draws the resolution screen.
 * 
 * @return int Returns 0 on success.
 */
int drawLeaderBoard();


/**
 * @brief Draws the resolution screen.
 * 
 * @return int Returns 0 on success.
 */
int drawResolution();


/**
 * @brief Handles button click events for the "Resolution 14C" button in the menu.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int res14C(int x, int y);


/**
 * @brief Handles button click events for the "Resolution 110" button in the menu.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int res110(int x, int y);


/**
 * @brief Handles button click events for the "Resolution 11A" button in the menu.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int res11A(int x, int y);


/**
 * @brief Handles button click events for the "Resolution 115" button in the menu.
 * 
 * @param x The x-coordinate of the mouse click.
 * @param y The y-coordinate of the mouse click.
 * @return int Returns 0 on success.
 */
int res115(int x, int y);

#endif

