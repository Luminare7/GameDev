//--------------------------------------LIBRARIES-----------------------------------------------------------------------------------------------
#include "Character.h"
#include "raymath.h"

//-------------------------------------------------------------CLASSES FUNCTIONS----------------------------------------------------------------

Character::Character(int winWidth, int winHeight) :
    windowHeight(winWidth),
    windowWidth(winHeight)
{
    width = texture.width/maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPosition()
{
    return Vector2{
        static_cast< float >(windowWidth)/2.0f - scale * (0.5f * width),   // (float) is a C-stye cast
        static_cast< float >(windowHeight)/2.0f - scale* (0.5f * height) 
    };
}

void Character::tick(float deltaTime)
{
    if(!getAlive()) return; //Se questo if statement viene triggerato (KO), tutto il resto non viene letto
    //worldPosLastFrame = worldPosition;
    if(IsKeyDown(KEY_A)) velocity.x -= 1.0; // Se in un if statement ho una sola riga di codice la posso mettere accanto all'if senza {}
    if(IsKeyDown(KEY_D)) velocity.x += 1.0;
    if(IsKeyDown(KEY_W)) velocity.y -= 1.0;
    if(IsKeyDown(KEY_S)) velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};

    float rotation{};

    if(rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPosition().x + offset.x, 
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f: rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPosition().x + offset.x - weapon.width * scale, 
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f: rotation = 0.f;    
    }

    // disegna la spada
    Rectangle source{0.f, 0.f, static_cast< float >(weapon.width) * rightLeft, static_cast< float >(weapon.height)};
    Rectangle dest{getScreenPosition().x + offset.x, getScreenPosition().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    // DrawRectangleLines(
    //    weaponCollisionRec.x,
    //   weaponCollisionRec.y,
    //  weaponCollisionRec.width,
    // weaponCollisionRec.height,
    //RED
    //);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f) 
    {
        setAlive(false);
    }
}

