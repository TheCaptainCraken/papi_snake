#include "raylib.h"
#include "raymath.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define TARGET_FPS 100
#define DESIRED_SPEED 5
#define LATO_QUADRICOLA 25

typedef struct {
    Vector2 pos, vel;
}SnakeHead;

void DrawQuadricola(Color, Color);
void DrawSnake(Vector2, Color);
Vector2 UpdateSnake(SnakeHead);
Vector2 Moves(Vector2);
bool CheckDeath(SnakeHead);

int main(int argc, char** argv) {
    int f = 1;
    const Color base_color_dark = {86, 200, 26, 255};
    const Color base_color_light = {126, 236, 82, 255};
    const Color snake_head_color ={255, 51, 0, 255};
    SnakeHead snake;
    Vector2 start_pos = {5, 5};
    Vector2 start_vel = {1, 0};
    snake.pos = start_pos;
    snake.vel = start_vel;
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "snake by craken & pbl");
    SetTargetFPS(TARGET_FPS);

    //terminate the game only if the user closes the window or the player is dead
    while (!WindowShouldClose() && !CheckDeath(snake)){
        //helo
        if(f % (TARGET_FPS/DESIRED_SPEED) == 0){
            snake.pos = UpdateSnake(snake);
            f = 1;
        }
        snake.vel = Moves(snake.vel);
        BeginDrawing(); 
            ClearBackground(RAYWHITE);
            DrawQuadricola(base_color_dark, base_color_light);
            DrawSnake(snake.pos, snake_head_color);
        EndDrawing();
        f++;
    }

    CloseWindow();
    return 0;
}

void DrawQuadricola(Color dark, Color light){
    int step = WINDOW_WIDTH / LATO_QUADRICOLA;

    for(int row = 0; row < LATO_QUADRICOLA; row++){
        for(int col = 0; col < LATO_QUADRICOLA; col++){
            Color current_color;
            if((row + col) % 2 == 0){
                current_color = dark;
            }else{
                current_color = light;
            }
            DrawRectangle(col * step, row * step, step, step, current_color);
        }
    }
}

void DrawSnake(Vector2 p, Color color){
    int step = WINDOW_WIDTH / LATO_QUADRICOLA;
    DrawRectangle(p.x * step, p.y * step, step, step, color);
}

Vector2 UpdateSnake(SnakeHead snake){
    return Vector2Add(snake.pos, snake.vel);
}

Vector2 Moves(Vector2 snake_vel){
    const Vector2 right = {1, 0};
    const Vector2 left = {-1, 0};
    const Vector2 up = {0, -1};
    const Vector2 down = {0, 1};
    if(IsKeyDown(KEY_RIGHT))
        return right;
    if(IsKeyDown(KEY_LEFT))
        return left;
    if(IsKeyDown(KEY_UP))
        return up;
    if(IsKeyDown(KEY_DOWN))
        return down;
    return snake_vel;
}

bool CheckDeath(SnakeHead snake){
    //if the snake is out on the left or right he's dead
    if(snake.pos.x < 0 || snake.pos.x > LATO_QUADRICOLA){
        return true;
    }
    //if the snake is out on the top or on the bottom he's dead
    if(snake.pos.y < 0 || snake.pos.y > LATO_QUADRICOLA){
        return true;
    }
    //else he's gucci
    return false;
}
//:)//
// Owo//
// :O
// XD
//O_o