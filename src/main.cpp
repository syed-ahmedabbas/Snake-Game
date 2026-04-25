#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

    Color bg = {10, 25, 60, 255}; //r,g,b,a
    
    int cSize = 20; 
    int cCount = 20;
    int offset = 75; //offset for the window size, we will add this to the window size to create a border around the game area

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

            Rectangle segment = Rectangle { offset + x , offset + y, (float)cSize, (float)cSize};
            DrawRectangleRounded(segment, 0.5, 8, {0, 200, 255, 255}); //draws a rounded rectangle with the specified parameters, 0.5 is the roundness of the corners, 8 is the number of segments used to draw the rounded corners, and the color is a bright green 

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

    void Reset(){
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}}; //reset the snake's body to the initial position
        direction = {1,0}; //reset the snake's direction to the initial direction
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
        DrawTexture(texture, offset + pos.x * cSize, offset + pos.y * cSize, WHITE); 

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
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game(){
        InitAudioDevice(); // initializes audio 
        eatSound = LoadSound("sounds/eat.mp3");
        wallSound = LoadSound("sounds/wall.mp3");
    }
    ~Game(){
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw(){
        food.Draw();
        snake.Draw();
    }
    void Update(){
        if(running){
            
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
        }
    }
    void CheckCollisionWithFood(){
        if(Vector2Equals(snake.body[0], food.pos)){ //add new segment to the end of the snake's body
            food.pos = food.GenerateRandomPos(snake.body); //generate new position for the food
            snake.addSegment = true;
            score++;
            PlaySound(eatSound);

        }
    }

    void CheckCollisionWithEdges(){
        if(snake.body[0].x == cCount || snake.body[0].x == -1){
            //game over
            GameOver();
    }
    if(snake.body[0].y == cCount || snake.body[0].y == -1)
    {
        //game over
        GameOver();
    }
    
}

    void GameOver(){
        snake.Reset();
        food.pos = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
        PlaySound(wallSound);
    }

    void CheckCollisionWithTail(){
        deque<Vector2> headlessBody = snake.body; //create a copy of the snake's body
        headlessBody.pop_front(); //remove the head of the snake from the copy of the
        if(ElementInDeque(snake.body[0], headlessBody)){ //check if the head of the snake is colliding with any other part of the snake's body
            GameOver();
        }
    }

 };

int main(){

    InitWindow(2*offset + cSize * cCount, 2*offset + cSize * cCount, "Snake Game"); // opens window
    SetTargetFPS(60); 
    Game game = Game();

    while(WindowShouldClose()==false){ //game loop

        //event handling

        //position
        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1){ //not moving opposite direction at the same time 
            game.snake.direction = Vector2{0, -1};
            game.running = true; //start the game when the player presses the up key for the first time
        }
        else if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1){
            game.snake.direction = Vector2{0, 1};
            game.running = true;
        }
        else if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1){
            game.snake.direction = Vector2{-1, 0};
            game.running = true;
        }
        else if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1){
            game.snake.direction = Vector2{1, 0};
            game.running = true;
        }
        //Draw
        BeginDrawing(); //start of drawing

        if(eventTriggered(0.2)){ //update the snake's position every 0.2 seconds
            game.Update();
        }

        ClearBackground(bg); //background color
        DrawRectangleLinesEx(Rectangle{(float)offset-5, (float)offset-5, (float)  cSize * cCount + 10, (float)  cSize * cCount + 10}, 5, Color{100, 180, 255, 255}); //draws a rectangle outline with the specified parameters, 5 is the thickness of the lines, and the color is white
        game.Draw(); //calling game
        DrawText("Snake Game", offset-5, 20, 20, WHITE); //draws the text "Snake Game" at the specified position with the specified font size and color)
        DrawText(TextFormat("Score: %d", game.score), offset - 5, offset + cSize * cCount + 10, 20, WHITE); //draws the text "Score: " followed by the current score at the specified position with the specified font size and color
        EndDrawing(); //end of drawing

    }
    CloseWindow(); //closes window

}