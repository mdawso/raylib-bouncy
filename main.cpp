#include "raylib.h"

// probably should have used defines
struct WindowSettings
{
    int w = 800;
    int h = 600;
    const char* title = "bouncy";
};

WindowSettings settings;

class BouncySquare
{
    public:

    float pos_x, pos_y;
    float size_x, size_y;
    Color colour;
    Vector2 velocity;

    BouncySquare(float pos_x, float pos_y, float size_x, float size_y, Color colour, Vector2 velocity) : pos_x(pos_x), pos_y(pos_y), size_x(size_x), size_y(size_y), colour(colour), velocity(velocity) {}

    int update(float dt) {
        pos_x += velocity.x * dt;
        pos_y += velocity.y * dt;
        if(pos_x < 0 || pos_x + size_x > settings.w)
        {
            velocity.x = -velocity.x;
        }
        if(pos_y < 0 || pos_y + size_y > settings.h)
        {
            velocity.y = -velocity.y;
        }
        DrawRectangle(pos_x, pos_y, size_x, size_y, colour);
        return 0;
    }
};

const int num_squares = 25;
BouncySquare* squares[num_squares];

int main()
{
    InitWindow(settings.w, settings.h, settings.title);
    SetTargetFPS(60);

    for(int i = 0; i < num_squares; i++) {
        float w = GetRandomValue(25,75);
        float h = GetRandomValue(25,75);
        float x = GetRandomValue(w, settings.w - w); 
        float y = GetRandomValue(h, settings.h - h);
        Color colour = {(unsigned char)GetRandomValue(0,255), (unsigned char)GetRandomValue(0,255), (unsigned char)GetRandomValue(0,255), 0xff};
        Vector2 velocity = {(float)GetRandomValue(-250,250), (float)GetRandomValue(-250,250)};
        squares[i] = new BouncySquare(x, y, w, h, colour, velocity);
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (BouncySquare* square : squares)
        {
            float dt = GetFrameTime();
            square->update(dt);
        }

        EndDrawing();
    }
    CloseWindow();
}