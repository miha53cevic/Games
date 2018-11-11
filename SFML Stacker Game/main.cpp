#include <SFML/Graphics.hpp>

//PROVJERAVA AKO SE PLATFORME DODRIJU / SIJEKU
//VRACA TOCNO AKO SE SIJEKU NETOCNO AKO SE NE SIJEKU
bool stacked(const sf::RectangleShape *platform, const int& size)
{
	sf::FloatRect r1 = platform[size - 1].getGlobalBounds();
	sf::FloatRect r2 = platform[size].getGlobalBounds();
	return r1.intersects(r2);
}

int main()
{
	//Variables
	int size = 5;
	bool dir = 1;
	float fspeed = 50.f;
	bool bGameOver = false;
	bool bLose = false;
	bool bWin = false;

	//Window
	sf::RenderWindow window(sf::VideoMode(480, 240), "Stacker SFML");
	window.setKeyRepeatEnabled(false);

	//FONT LOADING
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	//TEXT LOADING
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(64);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);

	//Array od platformi
	sf::RectangleShape platform[5];
	
	//DEFAULT SETTINGS OF ALL PLATFORMS
	for (auto &i : platform)
	{
		i.setFillColor(sf::Color::Color(128, 128, 128, 255));
		i.setSize({32, 32});
		i.setOrigin(16, 16);
	}

	//PRVA PLATFORMA & SCALE
	platform[size - 1].setScale(size, 1);
	platform[size - 1].setPosition(window.getSize().x / 2, window.getSize().y - 32);

	//Time for frame independent movement
	sf::Clock clock;
	sf::Time elapsed;

	while (window.isOpen())
	{
		elapsed = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				if (!stacked(platform, size) && size < 5)
				{
					bGameOver = true;
					bLose = true;
				}

				//Game Over && Check if platform stacked
				else if (size == 1)
				{
					bGameOver = true;
					bWin = true;
				}
				else
				{
					//DODAJ NOVU PLATFORMU && POVECAJ BRZINU
					fspeed += 200.f;
					size--;
					platform[size - 1].setScale(size, 1);
					platform[size - 1].setPosition((32 * (size / 2) + 16), platform[size].getPosition().y - 30); //BILO BI -32 ALI HOCU DA SE SIJEKU
				}
			}
		}

		if (!bGameOver)
		{
			//MOVE PLATFORM RIGHT
			if (dir == 1)
			{
				if (platform[size - 1].getPosition().x + (32 * (size / 2) + 16) > window.getSize().x)
				{
					dir = 0;
				}

				platform[size - 1].move(fspeed * elapsed.asSeconds(), 0);
			}
			//MOVE PLATFORM LEFT
			else if (dir == 0)
			{
				if (platform[size - 1].getPosition().x - (32 * (size / 2) + 16) < 0)
				{
					dir = 1;
				}

				platform[size - 1].move(-fspeed * elapsed.asSeconds(), 0);
			}
		}

		//CLEAR SCREEN
		window.clear(sf::Color::White);

		//DRAW THE PLATFORMS - ne treba staviti da radi samo ako je !bGameOver jer ih hocu videti i na kraju
		for (int i = 4; i >= size - 1; i--)
		{
			window.draw(platform[i]);
		}

		//WIN || LOSE
		if (bWin == true)
		{
			text.setString("You win!");
			window.draw(text);
		}
		else if (bLose == true)
		{
			text.setString("You lose!");
			window.draw(text);
		}

		//DISPLAY LAST FRAME
		window.display();
	}

	return 0;
}