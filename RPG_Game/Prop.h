#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPosition);
    Rectangle GetCollisionRec(Vector2 knightPosition);

private:
    Texture2D texture{};
    Vector2 worldPosition{};
    Vector2 screenPosition{};

    float scale{4.f};
};