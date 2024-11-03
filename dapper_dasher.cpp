#include "modules/score.cpp"
#include "modules/initialize.cpp"


bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // initializing project struct
    Dapper_dasher dapper_dasher;
    Path path;
    Labels labels;

    // initialize the window
    InitWindow(dapper_dasher.windowDimensions[0], dapper_dasher.windowDimensions[1], labels.dapperDasher);

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture(path.nebula);

    
    AnimData nebulae[dapper_dasher.sizeOfNebulae];

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


    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture(path.scarfy);
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = dapper_dasher.windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = dapper_dasher.windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    // is the rectanlge in the air?
    bool isInAir{};
    // jump velocity (pixels/second)
    const int jumpVel{-600};

    int velocity{0};

    Ground ground; 
    Texture2D background = LoadTexture(path.background);
    
    Texture2D midground = LoadTexture(path.midground);
    
    Texture2D foreground = LoadTexture(path.foreground);
    

    bool collision{};

    Score score;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the background
        Vector2 bg1Pos{ground.bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{ground.bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        // draw the midground
        Vector2 mg1Pos{ground.mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{ground.mgX + midground.width*2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        // draw the foreground
        Vector2 fg1Pos{ground.fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{ground.fgX + foreground.width*2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        // perform ground check
        if (isOnGround(scarfyData, dapper_dasher.windowDimensions[1]))
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        
        for (int i = 0; i < dapper_dasher.sizeOfNebulae; i++)
        {
            // update the position of each nebula
            nebulae[i].pos.x += nebVel * dT;
        }

        
        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfy's animation frame
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < dapper_dasher.sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        for (AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        
        //score
        runningScore(score.score);

        //high score
        highScore();

        if (collision)
        {
            // lose the game
            DrawText(labels.gameOver, dapper_dasher.windowDimensions[0]/4 + 20, dapper_dasher.windowDimensions[1]/2 - 20, 40, RED);
            
            //ask for restart game
            DrawText(labels.startAgain, dapper_dasher.windowDimensions[0]/4 - 40, dapper_dasher.windowDimensions[1] / 2 + 80, 20, WHITE);

            //check score
            checkHighScore(score.score);


            //restart
            restart(dapper_dasher,nebula,&scarfyData,nebulae,&ground,&score,&collision);

                
            
        }
     
        else
        {
            for (int i = 0; i < dapper_dasher.sizeOfNebulae; i++)
            {
                // draw nebula
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

            // Scroll background
            ground.bgX -= 20 * dT;
            if (ground.bgX <= -background.width*2)
            {
                ground.bgX = 0.0;
            }
            // Scroll the midground
            ground.mgX -= 40 * dT;
            if (ground.mgX <= -midground.width*2)
            {
                ground.mgX = 0.0;
            }
            // Scroll the foreground
            ground.fgX -= 80 * dT;
            if (ground.fgX <= -foreground.width*2)
            {
                ground.fgX = 0.0;
            }
            
            //addition of score
            addScore(&score.score,&score.scoreRunningTime,dT);
        }

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}
