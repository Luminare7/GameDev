#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}
void BaseCharacter::undoMovement()
{
    worldPosition = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPosition().x,
        getScreenPosition().y,
        width * scale,
        height * scale 
    };
}

void BaseCharacter::tick(float deltaTime) //la "virtual" declaration va solo nell'header (.h) file
{
    worldPosLastFrame = worldPosition;

    //Update animation frame
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if(frame > maxFrames) frame = 0;
    }

    if(Vector2Length(velocity) != 0.0)
    {
        //Set worldPosition = worldPosition + direction
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;  //verifico la condizione dopo ? ed eseguo la prima operazione se è verificata.
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    //Disegno l'omino Pippottino
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPosition().x, getScreenPosition().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE); 
}