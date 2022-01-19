#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) :  //Constructor
    worldPosition(pos),  //Member initializer list
    texture(tex)
{

}
void Prop::Render(Vector2 knightPosition)    //knightPosition è knight.worldPosition
{
    Vector2 screenPosition = Vector2Subtract(worldPosition, knightPosition);
    DrawTextureEx(texture, screenPosition, 0.f, scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 knightPosition)
{
    Vector2 screenPosition = Vector2Subtract(worldPosition, knightPosition);
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        texture.width * scale,
        texture.height * scale  
    };
}