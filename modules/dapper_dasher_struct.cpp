#include "raylib.h"

struct Dapper_dasher
{
    #define WIDTH 512
    #define HEIGHT 380

    const int windowDimensions[2] {
        WIDTH  
        ,HEIGHT 
    };
    const int sizeOfNebulae{100};
};

struct Labels
{
    const char dapperDasher[15] = "Dapper Dasher!";
    const char gameOver[11] = "GAME OVER";
    const char startAgain[27] = "PRESS SPACE TO START AGAIN";
};
struct Path
{
    const char scarfy[20] = "textures/scarfy.png";
    const char nebula[20] = "textures/nebula.png";
    const char midground[23] = "textures/midground.png";
    const char foreground[24] = "textures/foreground.png";
    const char background[24] = "textures/background.png";

    
};
struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};
struct Ground
{
    float bgX{}; //background
    float mgX{}; //midground
    float fgX{}; //foreground
};
struct  Score
{
    long score = 0;
    float scoreRunningTime = 0.0;
};
