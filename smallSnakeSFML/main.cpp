#include "Application.h"

int main()
{
	srand(time(0));

	Application app({ 1280, 720 }, "SmallSnakeSFML");

	while (!app.getWindow()->isDone())
	{
		if (!app.GameOver())
		{
			app.HandleInput();
			app.Update();
			app.Render();
			app.RestartClock();
		}

		if (app.GameOver())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				return 0;
			}
		}
	}

	return 0;
}