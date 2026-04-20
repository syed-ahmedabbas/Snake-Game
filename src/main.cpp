#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

    Color bg = {20, 60, 20, 255}; //r,g,b,a
    
    int cSize = 30; 
    int cCount = 20;

    double lastUpdateTime = 0.0; //controls the speed of the snake, we will update the snake's position every 0.1 seconds
    
    bool ElementInDeque( Vector2 element ,deque<Vector2> deque){
        for(unsigned int i = 0; i < deque.size(); i++){
            if(Vector2Equals(deque[i], element)){ //checks if the element is equal to any of the elements in the deque using the Vector2Equals function from raymath.h
                return true;
            }
        }        return false;
    }

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
    bool addSegment = false; //flag to indicate whether we need to add a new segment to the snake's body

    void Draw(){
        for (unsigned int i = 0; i < body.size(); i++){ //unsigned int to avoid warning about comparing signed and unsigned ints
            float x = body[i].x * cSize;
            float y = body[i].y * cSize;

            Rectangle segment = Rectangle { x, y, (float)cSize, (float)cSize};
            DrawRectangleRounded(segment, 0.5, 8, {57, 255, 20, 255}); //draws a rounded rectangle with the specified parameters, 0.5 is the roundness of the corners, 8 is the number of segments used to draw the rounded corners, and the color is a bright green 

    }
}
    void Update(){
        //growing length
         body.push_front(Vector2Add(body[0], direction)); //adds new head to the front of the deque in the direction the snake is moving
        if(addSegment == true){
            addSegment = false;
        }
        else {
        body.pop_back();
        }

        //collision
    }
};





class Food{
    public:
    Vector2 pos;
    Texture2D texture; 

    Food(deque<Vector2> snakeBody ){
        Image image = LoadImage("graphics/food.png"); // Load image from file into CPU memory (RAM);
        ImageResize(&image, 20, 20);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        pos = GenerateRandomPos(snakeBody);
    }

    ~Food(){
        UnloadTexture(texture);
    }

    void Draw(){
        DrawTexture(texture, pos.x * cSize, pos.y * cSize, WHITE); 

    }
    
    Vector2 GenerateRandomCell(){
        float x = GetRandomValue(0, cCount-1);
        float y = GetRandomValue(0, cCount-1);
        return Vector2{x,y};
    }




    Vector2 GenerateRandomPos(deque<Vector2> snakeBody){ //generate random position for the food, we will pass the snake's body as an argument to this function to ensure that the food does not spawn on top of the snake
        
        Vector2 pos = GenerateRandomCell();
        while(ElementInDeque(pos, snakeBody)){
            pos = GenerateRandomCell();
        }
        return pos;
    }

 };

 class Game{
public:

    Snake snake = Snake();
    Food food = Food(snake.body);
    
    void Draw(){
        food.Draw();
        snake.Draw();
    }
    void Update(){
        snake.Update();
        CheckCollisionWithFood();
    }
    void CheckCollisionWithFood(){
        if(Vector2Equals(snake.body[0], food.pos)){ //add new segment to the end of the snake's body
            food.pos = food.GenerateRandomPos(snake.body); //generate new position for the food
            snake.addSegment = true;
        }
    }
 };

int main(){

    InitWindow(cSize * cCount, cSize * cCount, "Snake Game"); // opens window
    SetTargetFPS(60); 
    Game game = Game();

    while(WindowShouldClose()==false){ //game loop

        //event handling

        //position
        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1){ //not moving opposite direction at the same time 
            game.snake.direction = Vector2{0, -1};
        }
        else if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1){
            game.snake.direction = Vector2{0, 1};
        }
        else if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1){
            game.snake.direction = Vector2{-1, 0};
        }
        else if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1){
            game.snake.direction = Vector2{1, 0};
        }
        //Draw
        BeginDrawing(); //start of drawing

        if(eventTriggered(0.2)){ //update the snake's position every 0.2 seconds
            game.Update();
        }
        ClearBackground(bg); //background color

        game.Draw(); //calling game

        EndDrawing(); //end of drawing

    }
    CloseWindow(); //closes window

}