#include <stdio.h>
#include <minix/sysutil.h>
#include <lcom/lcf.h>

#include <string.h>

extern struct real_time_clock_info rtc_info;
void save_name_score(char *name,int score);

void read_scores(char names[][10], int scores[], char dates[][18], int size);
