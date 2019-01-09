#include "Game.h"

int main()
{
    Game demo({384, 512}, "Breakout");

    while(!demo.getWindow()->isDone())
    {
        demo.HandleInput();
        demo.Update();
        demo.Render();

        demo.getElapsedTime();
    }

    return 0;
}
