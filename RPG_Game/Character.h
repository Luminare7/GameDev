//--------------------------------------LIBRARIES--------------------------------------------------------------------------------------------
#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

//-------------------------------------------------------------CLASSES-----------------------------------------------------------------------
class Character : public BaseCharacter   //Character cosi eredita direttamente da BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPosition() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; } //const significa che cio che riguarda questa funzione non verra cambiato
    void takeDamage(float damage); 

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};
#endif