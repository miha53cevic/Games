#pragma once

enum Direction { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

struct Player
{
	//Constructor
	Player(){}
	Player(sf::Color color)
	{
		circle.setRadius(3);
		circle.setFillColor(color);
		circle.setPosition(x, y);

		dir = Direction(rand() % 4);
	}

	int x = 0;
	int y = 0;

	Direction dir;
	sf::CircleShape circle;

	void update(const int& nScreenHeight, const int& nScreenWidth)
	{
		//Move Player
		if (dir == LEFT) x--;
		else if (dir == RIGHT) x++;
		else if (dir == UP) y--;
		else if (dir == DOWN) y++;

		//Ako je igrac izvan ekrana napravi da se stvori s druge strane ekrana
		if (x <= -1) x = nScreenWidth - 1;
		else if (x >= nScreenWidth) x = 0;
		else if (y <= -1) y = nScreenHeight - 1;
		else if (y >= nScreenHeight) y = 0;

		circle.setPosition(x, y);
	}
};