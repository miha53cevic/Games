#include "Engine/App.h"

int main()
{
	we::App demo;
	demo.CreateWindow(480, 640, "Derpy Bird");
	demo.setVSync(true);
	demo.Run();

	return 0;
}