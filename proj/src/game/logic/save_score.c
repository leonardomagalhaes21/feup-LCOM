#include "save_score.h"
#include <stdio.h>
#include <string.h>

void save_name_score(char *name, int score) {
    int scores[3] = {0, 0, 0};
    char names[3][10] = {"", "", ""};
    int c = 0;

    FILE *file = fopen("/home/lcom/labs/proj/src/scoreboard.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%9s %d", names[c], &scores[c]) != EOF && c < 3) {
            c++;
        }
        fclose(file);
    }

    for (int i = 0; i < 3; i++) {
        if (score > scores[i]) {
            for (int j = 2; j > i; j--) {
                scores[j] = scores[j - 1];
                strcpy(names[j], names[j - 1]);
            }
            scores[i] = score;
            strncpy(names[i], name, 9);
            names[i][9] = '\0'; // Ensure null-termination
            break;
        }
    }

    file = fopen("/home/lcom/labs/proj/src/scoreboard.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < 3; i++) {
        fprintf(file, "%s %d\n", names[i], scores[i]);
    }
    fclose(file);
}

void read_scores(char names[][10], int scores[], int size) {
    FILE *file = fopen("/home/lcom/labs/proj/src/scoreboard.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    int c = 0;
    while (c < size && fscanf(file, "%9s %d", names[c], &scores[c]) != EOF) {
        c++;
    }

    fclose(file);
}

