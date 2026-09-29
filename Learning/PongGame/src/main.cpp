#include <iostream>
#include <raylib.h>

using namespace std;

Color Purple = 

int player_score = 0;
int cpu_score = 0;


//Ball
class Ball{
    public:
    
    float x,y;
    int speed_x, speed_y;
    int radius;

    void Draw(){
        //Ball
        DrawCircle(x, y, radius, WHITE);
    }
    
    void Update(){

        //Speed Of Ball
        x += speed_x;
        y += speed_y;

        //Collisions
        if(y+radius >= GetScreenHeight()-10 || y-radius <= 10){
            speed_y *= -1;
        }
        if(x+radius >= GetScreenWidth()){
            cpu_score ++;
            ResetBall();
        }
        
        if(x-radius <= 10){
            player_score ++;
            ResetBall();

        }
    }

    void ResetBall(){
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];


    }
};

//Player Paddle
class Paddle{
    protected:
    void LimitMovement(){
        //Movement Restrictions
        if(y <= 0){
            y = 0;
        }
        if(y+height >= GetScreenHeight() ){
            y = GetScreenHeight() - height;
        }
    }
    
    public:

    float x,y;
    float height, width;
    int speed;

    void Draw(){
        //Paddle
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){

        //Paddle Movement
        if(IsKeyDown(KEY_UP)){
            y -= speed; 
        }
        else if(IsKeyDown(KEY_DOWN)){
            y += speed; 
        }

        LimitMovement();
    }
};

//Using Inheritense 
class CpuPaddle : public Paddle{
    
    public:
    void Update(int ball_y){
        
        //Cpu Logic
        if(y + height/2 > ball_y){
            y = y - speed;
        }
        if(y + height/2 <= ball_y){
            y = y + speed;
        }

        LimitMovement();
    }

};

//Ball Instance
Ball ball;

//Player Paddle Instance
Paddle player;

//Cpu Paddle  Instansce
CpuPaddle  cpu;

int main(){
    
    cout<<"Starting Game"<<endl;

    //Screen Size
    int screen_width = 1280;
    int screen_height = 800;

    InitWindow(screen_width, screen_height, "Pong Game");
    SetTargetFPS(60);

    //Ball
    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    //Player Paddle
    player.x = 10;
    player.y = screen_height / 2 - 60;
    player.height = 120;
    player.width = 25; 
    player.speed = 6;

    //Cpu Paddle
    cpu.x = screen_width -35;
    cpu.y = screen_height/2 -60;
    cpu.height = 120;
    cpu.width = 25;
    cpu.speed = 6;


    //Game Loop
    while(WindowShouldClose() == false){

        //Drawing
        BeginDrawing();

        //Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //Checking For Collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1;
        }
        
        //Clearing
        ClearBackground(BLACK);

        //Ball
        ball.Draw();

        //Paddle player
        player.Draw();

        //Paddle two
        cpu.Draw();

        //Line
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);

        //CPU Score
        DrawText(TextFormat("%i", cpu_score), 3*screen_width / 4 -20, 20, 80, WHITE);

        //Player Score
        DrawText(TextFormat("%i", player_score), screen_width / 4 -20, 20, 80, WHITE);

        EndDrawing();


    }

    CloseWindow();
    return 0;

}