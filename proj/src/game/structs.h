#ifndef STRUCTS_H_
#define STRUCTS_H_

struct real_time_clock_info{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};


struct user
{
    char name[20];
    char symbol;
    int score;
};


struct bullet
{
    int x;
    int y;
    int damage;
    float xDirection;
    float yDirection;
};





/*
struct board
{
    int width;
    int height;
    char **board;
};
*/

#endif

