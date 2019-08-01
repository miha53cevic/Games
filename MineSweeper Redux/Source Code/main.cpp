#include "Engine/App.h"

int main()
{
	we::App game;
	game.CreateWindow(1280, 720, "MineSweeper Redux");
	game.Run();

	return 0;
}