#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Snake
{
public:
	Snake(sf::Vector2u l_size, int l_BlockSize);
	~Snake();

	void Update();
	void Draw(sf::RenderWindow* window);
	void HandleInput();

	void growSnake();

	sf::Vector2i getSnakeHeadXY();

	bool CheckCollision();

private:

	enum Direction
	{
		LEFT, RIGHT, UP, DOWN
	};

	struct sTail
	{
		sTail(const int l_BlockSize)
		{
			shape.setSize(sf::Vector2f(l_BlockSize - 1, l_BlockSize - 1 ));
			shape.setFillColor(sf::Color::Green);
		}

		void Update()
		{
			shape.setPosition(x, y);
		}

		int x = 0, y = 0;
		sf::RectangleShape shape;
	};

	std::vector<sTail> Tails;

	Direction m_Direction;

	int nSnakeSize;

	sf::Vector2u m_windowSize;

	int m_BlockSize;
};

