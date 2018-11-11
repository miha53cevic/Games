#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML First Game!");
	
	sf::Texture player_tex;
	if (player_tex.loadFromFile("tex/PlayerTex.png"))
	{
		//Error
	}

	sf::Sprite player;
	player.setTexture (player_tex);
	sf::Vector2u p_size = player_tex.getSize();
	player.setOrigin(p_size.x / 2, p_size.y / 2);
	player.setPosition(window.getSize().x / 2, window.getSize().y / 2);

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
		}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		if (player.getPosition().x + (p_size.x / 2) < window.getSize().x)
			player.move(100 * elapsed.asSeconds(), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		if (player.getPosition().x - (p_size.x / 2) > 0)
			player.move(-100 * elapsed.asSeconds(), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (player.getPosition().y - (p_size.y / 2) > 0)
			player.move(0, -100 * elapsed.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (player.getPosition().y + (p_size.y / 2) < window.getSize().y)
			player.move(0, 100 * elapsed.asSeconds());
	}

		window.clear(sf::Color::White);
		window.draw(player);
		window.display();
	}

	return 0;
}