#include "save_score.h"

void save_score(int score) {
    int scores[3] = {0,0,0};
    int c = 0;

    FILE *file = fopen("/home/lcom/labs/proj/src/scoreboard.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d", &scores[c]) != EOF && c < 3) {
            c++;
        }

        fclose(file);
    }

    for (int i = 0; i <= 2; i++) {
      if (score > scores[i]) {
        for (int j = 2; j > i; j--) {
          scores[j] = scores[j - 1];
        }
        scores[i] = score;
        break;
      }
    }

    file = fopen("/home/lcom/labs/proj/src/scoreboard.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < 3; i++) {
      fprintf(file, "%d\n", scores[i]);
    }
    fclose(file);
}
