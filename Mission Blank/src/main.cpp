#include "game.h"

int main()
{
	srand(time(nullptr));

	Game game(sf::Vector2u(1280, 720), "My Program");
	
	while (!game.getWindow() -> IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}