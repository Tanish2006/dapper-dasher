#include "raylib.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "modules/valueLenght.cpp"

#define FILEPATH "data/high_score.txt"
#define UPDATETIME 2.0/12.0



void runningScore(long score)
{
    int scoreLength = valueLenghtLG(score);
    char scoreZero[(8 - scoreLength)];

    for(int scoreLoop = 0; scoreLoop < (8 - scoreLength); scoreLoop++)
    {
        strcat(scoreZero,"0");
    }
    //running score
    DrawText(TextFormat("%s%d",scoreZero,score), 10, 10, 20, WHITE);
        
}

void addScore(long *score,float *scoreRunningTime,float dT)
{
    *scoreRunningTime += dT;
    if(*scoreRunningTime >= UPDATETIME)
    {
        *score += 1;    
        *scoreRunningTime = 0.0;
    }
}

long readHighScore()
{
    //reading high score
    long highScore = 0;
    FILE *file = fopen(FILEPATH,"r");

    if (file == NULL){
       highScore = 0;
    }
    else
    {
        fscanf(file,"%ld", &highScore);
    }
    fclose(file); 
    return highScore;
}

void writeHighScore(long highScore)
{
    FILE *file = fopen(FILEPATH,"w");
    fprintf(file,"%ld",highScore);
    fclose(file); 
}

void highScore()
{
    long highScore = readHighScore();

    //draw high score
    DrawText(TextFormat("HI %d",highScore), 150, 10, 20, WHITE);
}

void checkHighScore(long score)
{
    long highScore = readHighScore();
    if(score > highScore)
    {
        writeHighScore(score);
    }
}