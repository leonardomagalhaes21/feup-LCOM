
updateMenuState();
updateGameState();
updatePauseState();
updateScoreboardState();
updateLeaderboardState();

void updateGameState() {
    switch (currentState) {
        case MENU:
            updateMenuState();
            break;
        case GAME:
            updateGameState();
            break;
        case PAUSE:
            updatePauseState();
            break;
        case SCOREBOARD:
            updateScoreboardState();
            break;
        case LEADERBOARD:
            updateLeaderboardState();
            break;
    }
}



