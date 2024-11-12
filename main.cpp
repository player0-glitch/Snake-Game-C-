#include <conio.h>
#include "include/game.h"

int main()
{
    Game snake_game;

    snake_game.Setup();
    snake_game.Run();

    /*while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(15);
    }*/

    return 0;
}
