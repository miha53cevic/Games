#include "game.h"

int main()
{
	Game game(sf::Vector2u(1024, 768), "Colour Wars Boom Edition");

	while (!game.getWindow() -> IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}