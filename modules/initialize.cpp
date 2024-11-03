#include "dapper_dasher_struct.cpp"

void initialize(struct Dapper_dasher dapper_dasher,Texture2D nebula,struct AnimData *scarfyData,struct AnimData *nebulae,struct Ground *ground,struct Score *score, bool *collision) 
{
    *collision = false;
                
    ground->bgX = 0.0;
    ground->mgX = 0.0;
    ground->fgX = 0.0;

    scarfyData->rec.x = 0;
    scarfyData->rec.y = 0;
    scarfyData->pos.x = dapper_dasher.windowDimensions[0]/2 - scarfyData->rec.width/2;
    scarfyData->pos.y = dapper_dasher.windowDimensions[1] - scarfyData->rec.height;
    scarfyData->frame = 0;
    scarfyData->updateTime = 1.0/12.0;
    scarfyData->runningTime = 0.0;
    for (int i = 0; i < dapper_dasher.sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = dapper_dasher.windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].pos.x =  dapper_dasher.windowDimensions[0] + i * 300;
    }
    score->score = 0;
    score->scoreRunningTime = 0;
}
void restart(struct Dapper_dasher dapper_dasher,Texture2D nebula,struct AnimData *scarfyData,struct AnimData *nebulae,struct Ground *ground,struct Score *score, bool *collision) 
{
    if(IsKeyPressed(KEY_SPACE))
    {
        initialize(dapper_dasher,nebula,scarfyData,nebulae,ground,score,collision);
    }
}