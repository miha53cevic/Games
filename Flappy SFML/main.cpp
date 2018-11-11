#include <SFML/Graphics.hpp>
#include <iostream>

//Provjerava da li je igrac udario pipe
bool PlayerVSWall(sf::Sprite Bird, sf::Sprite PipeUp, sf::Sprite PipeDown)
{
	sf::FloatRect rect = Bird.getGlobalBounds();

	if (rect.intersects(PipeUp.getGlobalBounds()))
		return true;

	else if (rect.intersects(PipeDown.getGlobalBounds()))
		return true;

	else return false;
}

int main()
{
	//Seed Time Generated
	srand(time(0));

	//Screen Variables
	const int nScreenHeight = 640;
	const int nScreenWidth = 480;

	//Render Window
	sf::RenderWindow window(sf::VideoMode(nScreenWidth, nScreenHeight), "Flappy SFML");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);

	//Texture Loading
	sf::Texture Sprite_Sheet;
	if (Sprite_Sheet.loadFromFile("tex/Sprite_Sheet.png"))
	{
		//Error
	}

	//Sprite Loading
	sf::Sprite Bird(Sprite_Sheet), Ground(Sprite_Sheet), PipeUp(Sprite_Sheet), PipeDown(Sprite_Sheet);

	Bird.setTextureRect({ 0, 0, 64, 64 });
	Ground.setTextureRect({ 0, 64, 640, 128});

	//Scale Bird to 32*32
	Bird.setScale(0.5f, 0.5f);

	//Sprite Defaults
	Ground.setOrigin({ 0, 128 });
	Ground.setPosition(0, nScreenHeight);

	Bird.setOrigin({ 32, 32 });
	Bird.setPosition(nScreenWidth / 3, nScreenHeight / 2);

	//Font Loading
	sf::Font font;

	if (!font.loadFromFile("fonts/Arial.ttf"))
	{
		// error...
	}

	//TEXT LOADING
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(64);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(5);
	
	text.setPosition(nScreenWidth / 2 - 16, nScreenHeight / 8);

	//	===	Game Variables	===	//
	bool bGameOver = false;
	bool bPipeDone = true;
	bool bScore = true;

	const int nGroundHeight = 128;	//128 predstavlja visinu poda y
	const int nSpaceHeight = 96;	//Razmak izmedu pipe-i
	
	sf::Vector2f velocity(0.f, 0.f);

	const float fJumpSpeed = -150.f;
	const float fGravity = 5.f;
	const float fScrollSpeed = -100;

	unsigned int nScore = 0;

	//Time & Clock
	sf::Clock clock;
	sf::Time fElapsed;

	//Main Game Loop
	while (window.isOpen())
	{
		fElapsed = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !bGameOver)
			{
				//Is the bird going to high?
				if (Bird.getPosition().y > 32) //Ako nije previsoko moze skociti
				{
					velocity.y = fJumpSpeed;
				}
			}
		}

		//Game Logic
		if (!bGameOver)
		{
			//Gravity
			velocity.y += fGravity;

			//Move Bird
			Bird.move(velocity.x * fElapsed.asSeconds(), velocity.y * fElapsed.asSeconds());

			//Change Bird Rotation
			if (velocity.y <= -10 && Bird.getRotation() != 330) // Ocito getRotation salje natrag ako je -5 365 stupnjeva
				Bird.rotate(-5);

			else if (velocity.y >= 50 && Bird.getRotation() != 90)
				Bird.rotate(5);

			//Is Bird on the ground?
			if (Bird.getPosition().y + (64 * Bird.getScale().y / 2) >= nScreenHeight - nGroundHeight)
				bGameOver = true;

			//Scroll Ground
			Ground.move(fScrollSpeed * fElapsed.asSeconds(), 0);	//Pomicanje u zemlje u x osi

			//Ako je kraj zemlje na x osi manji od duzine ekrana teleportiraj zemlju natrag na pocetno 0, nScreenHeight
			if (Ground.getPosition().x + 640 <= nScreenWidth)
				Ground.setPosition(0, nScreenHeight);

			//Create Pipe (min velicina u ovom primjeru je 64)
			int nPipeSize = rand() % (((nScreenHeight - nGroundHeight) - (64 * 2 + nSpaceHeight)) + 1) + 64; //Odreduje koliko je doljni dio visoki

			/*
				Note to self
				- Minimalna velicina oboje pipe je 64 u ovom primjeru
			*/

			if (bPipeDone)
			{
				//Create Pipe
				PipeUp.setTextureRect({ 896, 0, 64, nPipeSize });
				PipeUp.setPosition(nScreenWidth, (nScreenHeight - nGroundHeight) - nPipeSize);

				PipeDown.setTextureRect({ 960, 384 - ((nScreenHeight - nGroundHeight) - (nPipeSize + nSpaceHeight)), 64, ((nScreenHeight - nGroundHeight) - (nPipeSize + nSpaceHeight)) }); //Komplicirana i glupa formula
				PipeDown.setPosition(nScreenWidth, 0);

				bPipeDone = false;
			}

			//Move Pipes
			if (!bPipeDone)
			{
				PipeUp.move(fScrollSpeed * fElapsed.asSeconds(), 0);
				PipeDown.move(fScrollSpeed * fElapsed.asSeconds(), 0);
			}

			//Reset Pipe if at out of screen
			//Gleda se samo jedna jer ako je jedna pipe nestala je i automatski i druga s njom
			if (PipeUp.getPosition().x + 64 <= 0)
			{
				bPipeDone = true;
				//Ako je Pipe otisel iz ekrana stavi da se moze opet brojiti nScore
				bScore = true;
			}


			//Player VS Wall
			if (PlayerVSWall(Bird, PipeUp, PipeDown))
				bGameOver = true;

			/*
				Note To Self
				(64 * Bird.getScale().x ili .y)
				64 pocetna velicina
				Bird.getScale().x ili .y uzima scale factor
				npr. ako je scale 0.5f onda je 64 * 0.5f = 32
				*/

			//Add to nScore
			if (PipeUp.getPosition().x >= Bird.getPosition().x - (64 * Bird.getScale().x  / 2) && PipeUp.getPosition().x <= Bird.getPosition().x + (64 * Bird.getScale().x / 2) && bScore)
			{
				nScore++;

				//Da nema ovoga bi zbrajal vise puta dok bi prolazil, ovako gleda da ako je pogledal da nebude gledal tak dugo dok nebude nastal novi pipe
				bScore = false;
			}
		}

		//Drawing
		window.clear(sf::Color(0, 255, 255, 255));
		
		//Drawing Sprites
		window.draw(Bird);
		window.draw(Ground);

		//Drawing Pipe
		window.draw(PipeDown);
		window.draw(PipeUp);

		//Drawing Text / Score
		text.setString(std::to_string(nScore));
		window.draw(text);

		window.display();
	}

	return 0;
}