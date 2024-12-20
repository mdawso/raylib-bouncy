#include "raylib.h"

#define WINDOW_X 1600
#define WINDOW_Y 900
#define WINDOW_TITLE "bouncy"
#define gravity 9.81

#define NUM_SQUARES 250
#define VEL_CONSERVED_ON_COLLISION 0.6

struct Vector2i
{
    int x;
    int y;
};

class BouncySquare
{
    public:

    Vector2 pos;
    Vector2i size;
    Color colour;
    Vector2 velocity;
    
    Vector2 prev_pos;

    BouncySquare(Vector2 pos, Vector2i size, Color colour, Vector2 velocity) : pos(pos), size(size), colour(colour), velocity(velocity) {}

    int update(float dt) 
    {
        // apply linear velocities
        pos.x += velocity.x * dt;
        pos.y += velocity.y * dt;
        
        // collide with walls
        if(pos.x < 0 || pos.x + size.x > WINDOW_X)
        {
            pos = prev_pos;
            velocity.x = -velocity.x * VEL_CONSERVED_ON_COLLISION;
        }
        if(pos.y < 0 || pos.y + size.y > WINDOW_Y)
        {
            pos = prev_pos;
            velocity.y = -velocity.y * VEL_CONSERVED_ON_COLLISION;
        }
        
        // set prev pos for collisions
        prev_pos = pos;
        
        // apply gravity
        velocity.y += gravity;
        
        // draw the rect
        DrawRectangle(pos.x, pos.y, size.x, size.y, colour);
        return 0;
    }
};

BouncySquare* squares[NUM_SQUARES];

int main()
{
    InitWindow(WINDOW_X, WINDOW_Y, WINDOW_TITLE);
    SetTargetFPS(60);

    for(int i = 0; i < NUM_SQUARES; i++) 
    {
        // for each index in the squares array - init a new square object and give it random size, pos, colour and velocity
        Vector2i size = {GetRandomValue(25,75), GetRandomValue(25,75)};
        Vector2 pos = {(float)GetRandomValue(0, WINDOW_X - size.x), (float)GetRandomValue(0, WINDOW_Y - size.y)};
        Color colour = {(unsigned char)GetRandomValue(0,255), (unsigned char)GetRandomValue(0,255), (unsigned char)GetRandomValue(0,255), 0xff};
        Vector2 velocity = {(float)GetRandomValue(-250,250), (float)GetRandomValue(-250,250)};
        squares[i] = new BouncySquare(pos, size, colour, velocity);
    }

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        
        // for each square in the squares array run the update method
        for (BouncySquare* square : squares)
        {
            square->update(dt);
        }

        EndDrawing();
    }
    CloseWindow();
}