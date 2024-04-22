#include "gameViewer.h"



void renderMenuState();
void renderGameplayState();
void renderPauseState();
void renderVictoryState();
void renderDefeatState();

void renderGameState() {
    switch (currentState) {
        case MENU:
            renderMenuState();
            break;
        case GAME:
            renderGameState();
            break;
        case PAUSE:
            renderPauseState();
            break;
        case SCOREBOARD:
            renderScoreboardState();
            break;
        case LEADERBOARD:
            renderLeaderboardState();
            break;
    }
}
