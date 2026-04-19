#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

    Color bg = {20, 60, 20, 255}; //r,g,b,a
    
    int cSize = 30; 
    int cCount = 20;

    double lastUpdateTime = 0.0; //controls the speed of the snake, we will update the snake's position every 0.1 seconds
    
    bool eventTriggered(double interval){
        double currentTime = GetTime(); //returns the time in seconds since the program started
        if(currentTime - lastUpdateTime >= interval){
            lastUpdateTime = currentTime;
            return true;
        }
        return false;
    }// update the snake's position every 0.1 seconds, we will call this function in the game loop and check if it returns true before updating the snake's position
    
class Snake{
    public:
    deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}}; //deque is a double ended queue it allows us to add and remove elements from both ends of the queue
    Vector2 direction = Vector2{1,0}; //initial direction is right

    void Draw(){
        for (unsigned int i = 0; i < body.size(); i++){ //unsigned int to avoid warning about comparing signed and unsigned ints
            float x = body[i].x * cSize;
            float y = body[i].y * cSize;

            Rectangle segment = Rectangle { x, y, (float)cSize, (float)cSize};
            DrawRectangleRounded(segment, 0.5, 8, {57, 255, 20, 255}); //draws a rounded rectangle with the specified parameters, 0.5 is the roundness of the corners, 8 is the number of segments used to draw the rounded corners, and the color is a bright green 

    }
}
    void Update(){
        //movement
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction)); //adds new head and removes tail for movement



        //collision
    }
};





class food{
    public:
    Vector2 pos = GenerateRandomPos();
    Texture2D texture; 

    food(){
        Image image = LoadImage("graphics/food.png"); // Load image from file into CPU memory (RAM);
        ImageResize(&image, 20, 20);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~food(){
        UnloadTexture(texture);
    }

    void Draw(){
        DrawTexture(texture, pos.x * cSize, pos.y * cSize, WHITE); 

    }
    Vector2 GenerateRandomPos(){
        float x = GetRandomValue(0, cCount-1);
        float y = GetRandomValue(0, cCount-1);
        return Vector2{x,y};
    }
 };

int main(){

    InitWindow(cSize * cCount, cSize * cCount, "Snake Game"); // opens window
    SetTargetFPS(60); 
    food Food = food();
    Snake snake = Snake();
    

    while(WindowShouldClose()==false){ //game loop

        //event handling

        //position
        if(IsKeyPressed(KEY_UP) && snake.direction.y != 1){ //not moving opposite direction at the same time 
            snake.direction = Vector2{0, -1};
        }
        else if(IsKeyPressed(KEY_DOWN) && snake.direction.y != -1){
            snake.direction = Vector2{0, 1};
        }
        else if(IsKeyPressed(KEY_LEFT) && snake.direction.x != 1){
            snake.direction = Vector2{-1, 0};
        }
        else if(IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1){
            snake.direction = Vector2{1, 0};
        }
        //Draw
        BeginDrawing(); //start of drawing

        if(eventTriggered(0.2)){ //update the snake's position every 0.2 seconds
            snake.Update();
        }
        ClearBackground(bg); //background color

        Food.Draw(); //calling food
        snake.Draw(); //calling snake

        EndDrawing(); //end of drawing

    }
    CloseWindow(); //closes window

}