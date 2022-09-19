#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

#define WIDTH 32
#define HEIGHT 16

using namespace std;

enum E_rotation{STOP,RIGHT,LEFT,UP,DOWN, END};
E_rotation rotation;

struct point{
    int x,y;
};
vector <point> snake;
int fruitX,fruitY,
snakeX,snakeY, snakeLength=3;

bool isGameEnded = false;
vector <char> Screen;
void CreateCanvas();
void GameOver();

void Setup(){
    snakeX = WIDTH/2;
    snakeY = HEIGHT/2;
    rotation = STOP;
    isGameEnded = false;
    fruitX = rand() % (WIDTH-1)+1;
    fruitY = rand() % (HEIGHT-1)+1;
    snake.push_back({snakeX,snakeY});
    CreateCanvas();
}

void Input(){

    if(GetAsyncKeyState(VK_LEFT)){
        if(rotation!=RIGHT)
        rotation = LEFT;
    }
    else if(GetAsyncKeyState(VK_RIGHT)){
        if(rotation!=LEFT)
            rotation = RIGHT;
    }
    else if(GetAsyncKeyState(VK_UP)){
        if(rotation!=DOWN)
            rotation = UP;
    }
    else if(GetAsyncKeyState(VK_DOWN)){
        if(rotation!=UP)
            rotation = DOWN;
    }
    else if(GetAsyncKeyState(VK_ESCAPE)){
        rotation = END;
    }

}

void CreateCanvas(){

    //upper frame
    for(int x = 0; x++ < WIDTH+1;)
        Screen.push_back('#');
    Screen.push_back('\n');

    //middle section
    for(int y = 0; y++ < HEIGHT;){
        Screen.push_back('#');//left frame

        for(int x = 0; x++ < WIDTH;){
            Screen.push_back(' ');
        }
        Screen.push_back('#');//right frame
        Screen.push_back('\n');
    }

    //lower frame
    for(int x = 0; x++ < WIDTH+1;){
        Screen.push_back('#');
    }
}

void Draw(){

    if(Screen[snakeX+snakeY*(WIDTH+3)]!=' ') {

        if (fruitX == snakeX && fruitY == snakeY) {
            fruitX = rand() % (WIDTH-1)+1;
            fruitY = rand() % (HEIGHT-1)+1;
            snakeLength++;
        }
        else if(Screen[snakeX+snakeY*(WIDTH+3)] == '#' || snakeLength>3){
            GameOver();
            return;
        }
    }

    Screen[fruitX+fruitY*(WIDTH+3)] = '$';
    Screen[snakeX+snakeY*(WIDTH+3)] = '@';
    if(!snake.empty() && (snake.back().x != snakeX || snake.back().y != snakeY))
        snake.push_back({snakeX,snakeY});


    while(snake.size()>snakeLength){
        Screen[snake.front().x+snake.front().y*(WIDTH+3)] = ' ';
        snake.erase(snake.begin());
    }
    /*cout<<endl<<flush;
    system("CLS");*/
    cout<<string(Screen.begin(),Screen.end());
    cout<<endl<<"SCORE: "<<snakeLength-3<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

}

void Loop(){
    while (!isGameEnded){
        Draw();
        this_thread::sleep_for(chrono::milliseconds(200));
        Input();
        switch (rotation) {
            case STOP:
                break;
            case RIGHT:
                snakeX++;
                break;
            case LEFT:
                snakeX--;
                break;
            case UP:
                snakeY--;
                break;
            case DOWN:
                snakeY++;
                break;
            case END:
                return;
        }

    }
}

void GameOver(){
    isGameEnded = true;
    cout<<flush;
    system("CLS");
    cout<<"  _____                         ____                 \n"
          " / ____|                       / __ \\                \n"
          "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ \n"
          "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|\n"
          "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   \n"
          " \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   \n"
          "SCORE: "<<snakeLength-3;
    while(isGameEnded){
        Input();
        if(rotation==END)
        {
            return;
        }
    }
}

int main(int argc, char** argv) {
    Setup();
    Loop();
    return 0;
}