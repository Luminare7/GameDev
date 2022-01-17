#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    //Update running time
    data.runningTime += deltaTime;
        if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        //update animation frame
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
    
    int windowDimensions[] = {512, 380};   //width and height of the window

    //Apriamo subito la finestra di gioco
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");


    //Gravità  (p/s)/s   (l'apostrofo viene ignorato dal compiler, è solo per chiarezza nella lettura)
    const int gravity{1'000}; 

    int velocity{0};
    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float bgX{};
    float mgX{};
    float fgX{};
    bool collision{};

    //controllo se il rettangolo è in aria
    bool isInAir{};
    //velocità di salto pixels/sec
    const int jumpVel{-600};

    //nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    //AnimData for Nebula
    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae]{};  //Creo un array con due elementi di tipo animdata

    for ( int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = static_cast<float>(nebula.width/8);
        nebulae[i].rec.height = static_cast<float>(nebula.height/8);
        nebulae[i].pos.x = static_cast<float>(windowDimensions[0]) + 300 * i;
        nebulae[i].pos.y = static_cast<float>(windowDimensions[1] - nebula.height/8);
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    float finishLine{ nebulae[sizeOfNebulae - 1].pos.x};


    //nebula x velocity pix/s
    int nebulaVel{-200};

    //Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;

    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;

    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


    //Seleziono gli FPS 
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {


        //delta time = tempo dall'ultimo frame:
        const float dT{GetFrameTime()};

        //Comincia l'animazione
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20 * dT;
        mgX -= 40 * dT;
        fgX -= 80 * dT;


        if(bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }
        if(mgX <= -midground.width * 2)
        {
            mgX = 0.0;
        }
        if(fgX <= -foreground.width * 2)
        {
            fgX = 0.0;
        }        
        //draw the background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        //Draw the midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width*2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        //Draw the foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);



        if(isOnGround(scarfyData, windowDimensions[1]))
        {
        //Il rettangolo è a terra
        velocity = 0;
        isInAir = false;
        }
        else 
        {
        //Il rettangolo è per aria
        //apply gravity
        velocity += gravity * dT;
        isInAir = true;
        }

        //Controllo se ho saltato ed evito la possibilità di salto doppio
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        
        //aggiorna posizione di scarfy
        scarfyData.pos.y += velocity * dT;

        //aggiorna posizione nebula
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebulaVel * dT;
        }

        finishLine += nebulaVel * dT;

        //Update scarfy's animation frame
        if(!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
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
            if(CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        if(collision)
        {
            DrawText("Game Over, Brodo!", windowDimensions[0]/2, windowDimensions[1]/2, 50, RED);
        }
        else
        {
            if(finishLine >= 0.0 )
            {
                //Draw scarfy
                DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
                //Draw nebula
                for (int i=0; i < sizeOfNebulae; i++ )
                {
                    DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
                }
            }
            else if(finishLine <= 0.0)
            {
                DrawText("Victory!!!", windowDimensions[0]/2, windowDimensions[1]/2, 50, RED);
            }
        }


        //Finisci l'animazione
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();

}