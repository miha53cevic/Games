#include "Snake.h"

Snake::Snake(sf::Vector2u l_size, int l_blockSize) : nSnakeSize(3), m_Direction(LEFT)
{
	m_windowSize = l_size;
	m_BlockSize = l_blockSize;

	for (int i = 0; i < nSnakeSize; i++)
	{
		sTail tail(l_blockSize);
		tail.x = rand() % ((int)l_size.x / m_BlockSize + i) * m_BlockSize;
		tail.y = rand() % ((int)l_size.y / m_BlockSize) * m_BlockSize;
		tail.Update();

		Tails.push_back(tail);
	}
}
Snake::~Snake() {}

void Snake::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && m_Direction != RIGHT)
		m_Direction = LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && m_Direction != LEFT)
		m_Direction = RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_Direction != DOWN)
		m_Direction = UP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_Direction != UP)
		m_Direction = DOWN;
}

void Snake::Update()
{
	Tails.insert(Tails.begin(), Tails.front());
	Tails.pop_back();

	//Update Location
	if (m_Direction == RIGHT) Tails.front().x += m_BlockSize;
	else if (m_Direction == LEFT) Tails.front().x -= m_BlockSize;
	else if (m_Direction == DOWN) Tails.front().y += m_BlockSize;
	else if (m_Direction == UP) Tails.front().y -= m_BlockSize;

	//Change the tail rectangle loaction
	Tails.front().Update();

	//Check if snake is going out of the screen and move him to the oposite side
	if (Tails.front().x > (int)m_windowSize.x)
		Tails.front().x = 0;
	else if (Tails.front().x <=0)
		Tails.front().x = (int)m_windowSize.x;
	else if (Tails.front().y > (int)m_windowSize.y)
		Tails.front().y = 0;
	else if (Tails.front().y < 0)
		Tails.front().y = (int)m_windowSize.y;

	
}

void Snake::Draw(sf::RenderWindow* window)
{
	for (auto &i : Tails)
		window->draw(i.shape);
}

bool Snake::CheckCollision()
{
	//Gledaj samo rep pa je zato begin + 1
	for (std::vector<sTail>::iterator it = Tails.begin() + 1; it != Tails.end(); it++)
	{
			if (Tails.front().x == it->x && Tails.front().y == it->y)
			{
				return true;
			}	
	}

	return false;
}

void Snake::growSnake()
{
	Tails.push_back(Tails.back());
}

sf::Vector2i Snake::getSnakeHeadXY()
{
	return { Tails.front().x, Tails.front().y };
}