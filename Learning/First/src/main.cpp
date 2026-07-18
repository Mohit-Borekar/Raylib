#include <raylib.h>

int main(){
    
    InitWindow(800, 800, "First Game");
    SetTargetFPS(60);
    
    //Ball
    int BallX = 400;
    int BallY = 400;

    //Changing Color name = {red, blue, green, alpha};
    Color green = {20, 160, 133, 255};

    //Gmae Loop
    while (WindowShouldClose() == false){

        //Event Handling
        if(IsKeyDown(KEY_W)){
            BallY -= 3;
        }
        else if(IsKeyDown(KEY_A)){
            BallX -= 3;
        }
        else if(IsKeyDown(KEY_S)){
            BallY += 3;
        }
        else if(IsKeyDown(KEY_D)){
            BallX += 3;
        }
        
        //Position
        


        //Drawing
        BeginDrawing();

        //So it doesnt leave the trace
        ClearBackground(green);

        DrawCircle(BallX, BallY, 20, WHITE);

        EndDrawing();

    }
    
    CloseWindow();
    return 0;

}