#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"

int main()
{
	// ================================= State System ================================= //
	enum STATE
	{
		STATE_MENU,
		STATE_GAME,
		STATE_OVER
	} curState = STATE_MENU;

	// ================================= Screen Settings ================================= //
	const int nScreenWidth = 640;
	const int nScreenHeight = 480;

	// ================================= Window Settings ================================= //
	sf::RenderWindow window(sf::VideoMode(nScreenWidth, nScreenHeight), "SFML TRON - Mihael Petricevic");
	window.setVerticalSyncEnabled(true);

	// ================================= Sprites And Textures ================================= //
	sf::RenderTexture renderTex;
	renderTex.create(nScreenWidth, nScreenHeight);	//Create a render texture koja je x * y piksela velika
	renderTex.clear(sf::Color::Black);	//Clear RenderTexture

	sf::Sprite background(renderTex.getTexture());

	//Loading Menu Background
	sf::Texture texTile;

	texTile.setRepeated(true);
	texTile.setSmooth(true);

	if (texTile.loadFromFile("tex/Tile.png"))
	{
		//error
	}

	sf::Sprite tile(texTile);
	tile.setTextureRect({ 0, 0, nScreenWidth, nScreenHeight });

	//Loading font and text
	sf::Font font;
	if (font.loadFromFile("font/arial.ttf"))
	{
		//error
	}

	sf::Text text[3];
	for (size_t i = 0; i < 3; i++)
	{
		text[i].setFont(font);
		text[i].setOutlineColor(sf::Color::Black);
		text[i].setOutlineThickness(5);
	}

	// ================================= Game Variables ================================= //
	std::vector<bool> vecGameMap(nScreenHeight * nScreenWidth, false);

	int nWon = -1; //1 = Prvi igrac, 2 = Drugi igrac, 3 = Treci, 4 = Cetvrti, 0 Tie

	//Calling Player Objects
	Player p1(sf::Color::Blue);
	Player p2(sf::Color::Green);

	//Default Player COORDS
	p1.x = rand() % nScreenWidth;
	p1.y = rand() % nScreenHeight;

	p2.x = rand() % nScreenWidth;
	p2.y = rand() % nScreenHeight;

	//Lambda Function za 2D kordinate na 1D kordinate
	auto COORD = [nScreenWidth](int x, int y)
	{
		return (y * (nScreenWidth)) + x;
	};


	// ================================= LAMBDA FUNKCIJE ================================= //

	//Lambda Create A Animation When Mouse is over text[1] and text[2]
	auto TextAnimation = [&](int OriginalSize, int AnimationSize)
	{
		//Check if mouse is over the text buttons and make them bigger (mala animacija)
		sf::IntRect rect1(text[1].getGlobalBounds());
		sf::IntRect rect2(text[2].getGlobalBounds());

		if (rect1.contains(sf::Mouse::getPosition(window)))
		{
			text[1].setCharacterSize(AnimationSize);
		}
		else text[1].setCharacterSize(OriginalSize);

		if (rect2.contains(sf::Mouse::getPosition(window)))
		{
			text[2].setCharacterSize(AnimationSize);
		}
		else text[2].setCharacterSize(OriginalSize);
	};

	//Lambda Restart All Variables - ne treba mi ta bas lambda ali resetiram dvaput pa da se kod ne ponavlja
	auto RestartVariables = [&]()
	{
		nWon = -1;
		renderTex.clear(sf::Color::Black);

		std::fill(vecGameMap.begin(), vecGameMap.end(), 0);

		p1.x = rand() % nScreenWidth;
		p1.y = rand() % nScreenHeight;

		p2.x = rand() % nScreenWidth;
		p2.y = rand() % nScreenHeight;
	};

	// === Main Game Loop === //
	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Event Handler for input

			// === Control Layout === //
			if (curState == STATE_GAME)
			{
				//Player 1
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A && p1.dir != RIGHT)
					p1.dir = LEFT;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D && p1.dir != LEFT)
					p1.dir = RIGHT;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && p1.dir != DOWN)
					p1.dir = UP;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S && p1.dir != UP)
					p1.dir = DOWN;

				//Player 2
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && p2.dir != RIGHT)
					p2.dir = LEFT;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && p2.dir != LEFT)
					p2.dir = RIGHT;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && p2.dir != DOWN)
					p2.dir = UP;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && p2.dir != UP)
					p2.dir = DOWN;
			}
		}

		// ================================= States ================================= //
		switch (curState)
		{
			case STATE_MENU:
			{
				//MENU TEXT
				text[0].setCharacterSize(64);
				text[0].setString("TRON SFML");

				text[1].setPosition(0, 128);
				text[1].setCharacterSize(48);
				text[1].setString("Start");

				text[2].setPosition(0, 192);
				text[2].setCharacterSize(48);
				text[2].setString("Exit");

				//Treba pretvoriti GlobalBOunds iz float na int jer MousePos Salje int natrag
				sf::IntRect rect1(text[1].getGlobalBounds());	//Start
				sf::IntRect rect2(text[2].getGlobalBounds());	//Quit

				//Calling Lambda Function that creates a animation when hovering over text
				TextAnimation(48, 64);

				//Pogledaj ako je igrac kliknuo na koji text gumb
				if ((rect1.contains(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					curState = STATE_GAME;
				}

				if ((rect2.contains(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					window.close();
				}

				break;
			}

			case STATE_GAME:
			{
				//PLACE VISITED
				vecGameMap[COORD(p1.x, p1.y)] = true;
				vecGameMap[COORD(p2.x, p2.y)] = true;

				//Move Players in their direction
				p1.update(nScreenHeight, nScreenWidth);
				p2.update(nScreenHeight, nScreenWidth);

				//Draw Trails
				renderTex.draw(p1.circle);	//Nacrtaj na rendertexturu kruga koji je na kordinatama x i y
				renderTex.draw(p2.circle);
				renderTex.display(); //Prikazi sve sto je nacrtano na texturi tj. Updataj teksturu

				//Check If Player Has Collided
				if (vecGameMap[COORD(p1.x, p1.y)] == false && vecGameMap[COORD(p2.x, p2.y)] == true)	//Player 1 wins
					nWon = 1;
				else if (vecGameMap[COORD(p1.x, p1.y)] == true && vecGameMap[COORD(p2.x, p2.y)] == false)	//Player 2 wins
					nWon = 2;
				else if (vecGameMap[COORD(p1.x, p1.y)] == true && vecGameMap[COORD(p2.x, p2.y)] == true)	//Tie
					nWon = 0;

				//Ako je je netko pobjedil ili je tie pronheni state u STATE_OVER
				if (nWon != -1)
					curState = STATE_OVER;
					
				break;
			}

			case STATE_OVER:
			{
				//Find out who won
				text[0].setCharacterSize(64);
				switch (nWon)
				{
					case 1:
					{
						text[0].setString("Player Blue Wins!");
						break;
					}
					case 2:
					{
						text[0].setString("Player Green Wins!");
						break;
					}
					case 0:
					{
						text[0].setString("It's a Tie!");
						break;
					}
				}

				//Restart or go back to menu
				text[1].setPosition(0, 128);
				text[1].setCharacterSize(48);
				text[1].setString("Restart");

				text[2].setPosition(0, 192);
				text[2].setCharacterSize(48);
				text[2].setString("Back to menu");

				TextAnimation(48, 64);

				//Treba pretvoriti GlobalBOunds iz float na int jer MousePos Salje int natrag
				sf::IntRect rect1(text[1].getGlobalBounds());	//Restart
				sf::IntRect rect2(text[2].getGlobalBounds());	//Back to menu

				//Pogledaj ako je igrac kliknuo na koji text gumb
				if ((rect1.contains(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					curState = STATE_GAME;

					//Restart all variables
					RestartVariables();
				}

				if ((rect2.contains(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					curState = STATE_MENU;

					//Restart all variables zato jer ako onda igrac zapocne opet igru zapocne staru pa zato za svaki slucaj i tu resetiram
					RestartVariables();
				}
				
				break;
			}
		}

		// ================================= DRAWING ================================= //

		//Clear Screen
		window.clear(sf::Color::Black);

		//Draw

		if (curState == STATE_GAME || curState == STATE_OVER)
			window.draw(background);

		if (curState == STATE_MENU)
		{
			window.draw(tile);

			window.draw(text[0]);
			window.draw(text[1]);
			window.draw(text[2]);
		}

		if (curState == STATE_OVER)
		{
			window.draw(text[0]);
			window.draw(text[1]);
			window.draw(text[2]);
		}

		//Display
		window.display();
	}

	return 0;
}