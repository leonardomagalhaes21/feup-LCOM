#ifndef STRUCTS_H_
#define STRUCTS_H_




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

struct enemy
{
    int life;
    int damage;
    int x;
    int y;
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

