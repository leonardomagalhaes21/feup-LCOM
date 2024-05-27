#include "save_score.h"
#include "../../devices/rtc/rtc.h"

struct scoreboard_entry{
    char name[10];
    int score;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

void save_name_score(char *name, int score) {
  //initialize variables
  struct scoreboard_entry scores[10];
  struct scoreboard_entry temp_score;
  struct scoreboard_entry new_score;

  //load new score onto struct
  while(read_rtc_time()) {
    ;
  }
  strncpy(new_score.name, name, 9);
  new_score.name[9] = '\0';
  new_score.score = score;
  new_score.seconds = rtc_info.seconds;
  new_score.minutes = rtc_info.minutes;
  new_score.hours = rtc_info.hours;
  new_score.day = rtc_info.day;
  new_score.month = rtc_info.month;
  new_score.year = rtc_info.year;

  //flag to tell if players score has been saved
  int placed = 0;

  int c = 0;
  FILE *file = fopen("/home/lcom/labs/proj/src/scoreboard.txt", "r");
  if (file != NULL) {
    int line_result = fscanf(file, "%9s, %d, %hhu:%hhu:%hhu - %hhu/%hhu/%hhu\n",temp_score.name, &temp_score.score, &temp_score.hours, &temp_score.minutes, &temp_score.seconds, &temp_score.day, &temp_score.month, &temp_score.year);
    while (line_result != 0 && c < 10) {
      //found right place for the players score in array
      if(placed == 0 && temp_score.score < score){
        scores[c] = new_score;
        c++;
        placed = 1;
      }
      //add read score onto array
      scores[c] = temp_score;
      c++;
      line_result = fscanf(file, "%9s, %d, %hhu:%hhu:%hhu - %hhu/%hhu/%hhu\n",temp_score.name, &temp_score.score, &temp_score.hours, &temp_score.minutes, &temp_score.seconds, &temp_score.day, &temp_score.month, &temp_score.year);
    }
    if (placed == 0 && c < 10) {
        scores[c] = new_score;
        c++;
    }


    fclose(file);
  }

  //write all scores onto file again
  file = fopen("/home/lcom/labs/proj/src/scoreboard.txt", "w");
  if (file == NULL) {
    perror("Failed to open file");
    return;
  }
  for (int i = 0; i < c; i++) {
    fprintf(file, "%s, %d, %d:%d:%d - %d/%d/%d\n",scores[i].name, scores[i].score, scores[i].hours, scores[i].minutes, scores[i].seconds, scores[i].day, scores[i].month, scores[i].year);
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

