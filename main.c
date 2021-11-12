#include "raylib.h"
#include "raymath.h"

//width and hegiht in pixels of the window
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
//real fps and number of pfs that the player can see
#define TARGET_FPS 100
#define DESIRED_GAME_SPEED 5
//how many quads should the gameboard have 25 * 25
#define NUMERO_QUADRETTI_QUADRICOLA 25

//struct for the head of the snake
typedef struct {
    Vector2 pos, vel;
}SnakeHead;

//draws the game board
void DrawQuadricola(Color, Color);
//draws the snake
void DrawSnake(Vector2, Color);
//updates the snake's position using its velocity
Vector2 UpdateSnake(SnakeHead);
//fetches player input
Vector2 Moves(Vector2);
//checks if the bitch is fucking dead
bool CheckDeath(SnakeHead);

int main(int argc, char** argv) {
    int f = 1;//used for simulating the players fps

    const Color base_color_dark = {86, 200, 26, 255};
    const Color base_color_light = {126, 236, 82, 255};
    const Color snake_head_color ={255, 51, 0, 255};

    //creating a snake
    SnakeHead snake;
    Vector2 start_pos = {5, 5};
    Vector2 start_vel = {1, 0};
    snake.pos = start_pos;
    snake.vel = start_vel;
    
    //create the window and set the max fps
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "snake by craken & pbl");
    SetTargetFPS(TARGET_FPS);

    //terminate the game only if the user closes the window or the player is dead
    while (!WindowShouldClose() && !CheckDeath(snake)){
        //helo
        //every real fps / desired fps update the snake's position
        if(f % (TARGET_FPS/DESIRED_GAME_SPEED) == 0){
            snake.pos = UpdateSnake(snake);
            f = 1;
        }
        //fetch input and modify the velocity accordingly
        snake.vel = Moves(snake.vel);
        //raylib drawing
        BeginDrawing(); 
            ClearBackground(RAYWHITE);
            DrawQuadricola(base_color_dark, base_color_light);
            DrawSnake(snake.pos, snake_head_color);
        EndDrawing();
        f++;//every frame count it (used for simulating lower fps for the player)
    }

    CloseWindow();
    return 0;
}

//simply draws a chess like game board with dark green and light green
void DrawQuadricola(Color dark, Color light){
    int step = WINDOW_WIDTH / NUMERO_QUADRETTI_QUADRICOLA;

    for(int row = 0; row < NUMERO_QUADRETTI_QUADRICOLA; row++){
        for(int col = 0; col < NUMERO_QUADRETTI_QUADRICOLA; col++){
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

//draws a snake in the snakes position
void DrawSnake(Vector2 p, Color color){
    int step = WINDOW_WIDTH / NUMERO_QUADRETTI_QUADRICOLA;
    DrawRectangle(p.x * step, p.y * step, step, step, color);
}

//moves the snake using its velocity
Vector2 UpdateSnake(SnakeHead snake){
    return Vector2Add(snake.pos, snake.vel);
}

//fetches player input and modifies the snake's velocity
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

//checks if the snake is dead
bool CheckDeath(SnakeHead snake){
    //if the snake is out on the left or right he's dead
    if(snake.pos.x < 0 || snake.pos.x > NUMERO_QUADRETTI_QUADRICOLA){
        return true;
    }
    //if the snake is out on the top or on the bottom he's dead
    if(snake.pos.y < 0 || snake.pos.y > NUMERO_QUADRETTI_QUADRICOLA){
        return true;
    }
    //else he's gucci
    return false;
}