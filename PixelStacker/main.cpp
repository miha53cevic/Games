#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

bool isConnected(sf::Sprite object1, sf::Sprite object2)
{
	sf::FloatRect b = object2.getGlobalBounds();
	sf::FloatRect a = object1.getGlobalBounds();

	return a.intersects(b);
}

int main()
{
	//Variables
	const int nScreenHeight = 20;
	const int nScreenWidth = 30;
	const int nPixelSize = 16;

	const int w = nScreenWidth * nPixelSize;
	const int h = nScreenHeight * nPixelSize;

	bool bDir = 1; //0 = left, 1 = right
	bool bGameOver = false;
	bool bWin = false;

	int nSpeed = 500; //In miliseconds

	//Render Window
	sf::RenderWindow window(sf::VideoMode(w, h), "PixelStacker");
	window.setKeyRepeatEnabled(false);

	//Texture loading
	sf::Texture tex1, tex2;

	if (tex1.loadFromFile("tex/Gray_Tile.png")) {} //Error
	if (tex2.loadFromFile("tex/Tile.png")) {} //Error

	tex1.setRepeated(true);

	//Sprite
	sf::Sprite player(tex1);
	sf::Sprite background(tex2);

	//Player
	int nSize = 5;
	const int nOriSize = nSize;
	player.setPosition(w / 2, h - nPixelSize);

	//Blocks
	std::vector<sf::Sprite> blocks(nSize);
	
	//First Block
	sf::Sprite block(tex1);
	//The texture is repeated by the amount of blocks needed for that platform which we know by nSize
	block.setTextureRect({ 0, 0, nPixelSize * nSize, nPixelSize });
	block.setPosition(player.getPosition().x, player.getPosition().y);
	blocks.push_back(block);
	
	//FONT LOADING
	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// error...
	}

	//TEXT LOADING
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(64);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);

	//Time
	sf::Time elapsed;
	sf::Clock clock;
	sf::Time timePassed;

	while (window.isOpen())
	{
		elapsed = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//Keyboard
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				nSize--;

				player.setPosition(0, player.getPosition().y - nPixelSize + 1); //+1 tako da mogu provjeriti ako se doticu i da ne moram algoritme delati :P
				bDir = 1; //Smjer je desno jer je igrac na lijevom rubu se stvara svaki put kad stavi platformu

				//Creating new platform made of blocks
				sf::Sprite block(tex1);

				//The texture is repeated by the amount of blocks needed for that platform which we know by nSize
				block.setTextureRect({ 0, 0, nPixelSize * nSize, nPixelSize });
				block.setPosition(player.getPosition().x, player.getPosition().y);
				blocks.push_back(block);

				//Check for if connected to last piece
				if (nSize != nOriSize - 1 && !bGameOver && !bWin)
				{
					//Gledaju se predzadnji i onaj iza njega jer je zadnji u vectori onaj koji se krece kao player
					if (!isConnected(blocks[blocks.size() - 2], blocks[blocks.size() - 3]))
					{
						bGameOver = true;
					}

					else if (nSize == 0) bWin = true;

					//std::cout << bGameOver;
				}

				//Increase Speed :)
				nSpeed -= 100;
			}
		}

		//Sve dok igra traje pokreci playera i logiku igre
		if (!bGameOver && !bWin)
		{
			//Use time to make the player move slower | nSpeed in miliseconds
			if (timePassed.asMilliseconds() > nSpeed)
			{
				//Sets timePassed to 0
				timePassed -= timePassed;

				//Blocks number
				int activeBlock = blocks.size() - 1;

				//Move Player | 0 = left, 1 = right |
				if (bDir == 0)
				{
					player.move(-1 * nPixelSize, 0);
					blocks[activeBlock].move(-1 * nPixelSize, 0);
				}
				else if (bDir == 1)
				{
					player.move(1 * nPixelSize, 0);
					blocks[activeBlock].move(1 * nPixelSize, 0);
				}
			}
			//Time passed gets the time between frames and gets to be a higher number
			else timePassed += elapsed;


			//Check if player out of bounds
			if (player.getPosition().x == 0) bDir = 1;
			else if (player.getPosition().x + ((nSize - 1) * nPixelSize) == w - nPixelSize) bDir = 0;

			window.clear(sf::Color::White);

			//Draw Background
			for (int i = 0; i < nScreenHeight; i++)
				for (int j = 0; j < nScreenWidth; j++)
				{
					background.setPosition(j * nPixelSize, i * nPixelSize);
					window.draw(background);
				}
		}

		//Draw Player
		window.draw(player);

		//Draw Blocks of the player
		for (auto &i : blocks)
		{
			window.draw(i);
		}
		
		if (bGameOver)
		{
			text.setString("You lose!");
			window.draw(text);
		}
		else if (bWin)
		{
			text.setString("You win!");
			window.draw(text);
		}

		window.display();
	}

	return 0;
}