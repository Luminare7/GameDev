//--------------------------------------LIBRARIES-----------------------------------------------------------------------------------------

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>


//-------------------------------------------------------------MAIN-----------------------------------------------------------------------

int main()
{
    //costante con i valori delle dimensioni della finestra di gioco
    const int windowDimensions[] = {384, 384}; 

    //Apriamo la finestra di gioco
    InitWindow(windowDimensions[0], windowDimensions[1], "Pippottino fight!");

    //Carico l'immagine della mappa
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0, 0.0};
    const float mapScale{4.0f};

    SetTargetFPS(60);

    Character knight(windowDimensions[0], windowDimensions[1]);
    
    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };
    Enemy goblin{
        Vector2{800.f, 300.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };


    Enemy slime {
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);

        //Disegno la mappa nella finestra
        DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);

        //Disegna gli ostacoli (props)
        for (auto prop : props) //looppo per ciascun elemento (prop) in props
        {
            prop.Render(knight.getWorldPosition());
        }

        if(!knight.getAlive()) //Character dead
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue; //Dentro un loop, quando è raggiunto allora viene ignorato il resto del loop e comincia l'iterazione successiva
        }
        else                   //Character alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());
        //Check map bounds
        if (knight.getWorldPosition().x < 0.f ||
            knight.getWorldPosition().y < 0.f ||
            knight.getWorldPosition().x + windowDimensions[0] > map.width * mapScale ||
            knight.getWorldPosition().y + windowDimensions[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }
        for (auto prop : props)
        {
            if (CheckCollisionRecs(knight.GetCollisionRec(), prop.GetCollisionRec(knight.getWorldPosition()))) 
            {
                knight.undoMovement();
            }
        }
        
        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->GetCollisionRec(), knight.GetCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        

        EndDrawing();
    }

    CloseWindow();
}