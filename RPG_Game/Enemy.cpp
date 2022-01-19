#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPosition = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
  
    width = texture.width/maxFrames;
    height = texture.height;
    speed = 3.f;
}

void Enemy::tick(float deltaTime)
{
    if(!getAlive()) return;
    //worldPosLastFrame = worldPosition;
    //get the toTarget vector
    velocity = Vector2Subtract(target->getScreenPosition(), getScreenPosition());
    if(Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);  
    if(CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPosition()
{
    return Vector2Subtract(worldPosition, target->getWorldPosition());
}