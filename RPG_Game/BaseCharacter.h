#ifndef BASE_CHARACTER_H //Controlliamo se un file con questo nome non fosse già stato caricato nel main.cpp
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPosition() { return worldPosition; }
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPosition() = 0; //l'= 0 la rende una funzione puramente virtuale. BaseCharacter è adesso un'abstract class
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPosition{};  //position of the map (coordinate angolo alto a sx della finestra rispetto ad angolo alto a sx della mappa)
    Vector2 worldPosLastFrame{};
    //Value of 1: facing right direction, -1: facing let direction
    float rightLeft{1.f};  

    //Variabili per l'animazione del Pippottino
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f/12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool alive{true};

};

#endif