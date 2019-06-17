#include "mihaSimpleSFML.h"
#include "sResourceManager.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#define SPRITE_SIZE 64

#define CELL_SIZE 64
#define BOMB_COUNT 8

enum class CELL_STATE
{
	CLOSED, OPENED, BOMB
};

struct sCell
{
	sCell(sf::Vector2f pos)
	{
		state = CELL_STATE::CLOSED;

		sprite.setSize(sf::Vector2f(SPRITE_SIZE, SPRITE_SIZE));
		sprite.setTexture(&sResourceManager::get().getTexture("closed_cell"));
		sprite.scale((float)CELL_SIZE / SPRITE_SIZE, (float)CELL_SIZE / SPRITE_SIZE);

		sprite.setPosition(pos);

		neighbour_count = 0;

		flagged = false;
	}

	void ChangeTexture(std::string texName, sf::IntRect rect)
	{
		sprite.setTexture(&sResourceManager::get().getTexture(texName));
		sprite.setTextureRect(rect);
	}

	sf::RectangleShape sprite;

	int neighbour_count;

	bool flagged;

	CELL_STATE state;
};

class sMineSweeper : public mihaSimpleSFML
{
public:
	sMineSweeper() {}

private:
	std::vector<sCell> m_board;

	bool GameOver;

	sf::Text m_text;

	int convertCoord(int x, int y)
	{
		return (y * (ScreenWidth() / CELL_SIZE)) + x;
	}

	int isBomb(int x, int y)
	{
		if (m_board.at((y * (ScreenWidth() / CELL_SIZE)) + x).state == CELL_STATE::BOMB)
		{
			return 1;
		}
		else return 0;
	}

protected:
	virtual void Event(sf::Event e)
	{
		if (!GameOver)
		{
			// Get mouse click left or right
			// Left open space
			// Right place flag
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int x = sf::Mouse::getPosition(*getWindow()).x / CELL_SIZE;
				int y = sf::Mouse::getPosition(*getWindow()).y / CELL_SIZE;

				if (m_board.at(convertCoord(x, y)).state == CELL_STATE::CLOSED)
				{
					int rectMultiplier = m_board.at(convertCoord(x, y)).neighbour_count;

					m_board.at(convertCoord(x, y)).state = CELL_STATE::OPENED;
					m_board.at(convertCoord(x, y)).ChangeTexture("cells", sf::IntRect(sf::Vector2i(rectMultiplier * SPRITE_SIZE, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
				}
				else if (m_board.at(convertCoord(x, y)).state == CELL_STATE::BOMB) // Check if bomb was clicked
				{
					// if the game has ended show all bombs
					for (auto &i : m_board)
					{
						if (i.state == CELL_STATE::BOMB)
							i.ChangeTexture("bomb", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
					}

					// Clicked bomb has a red background
					m_board.at(convertCoord(x, y)).ChangeTexture("bomb_red", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));

					GameOver = true;
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				int x = sf::Mouse::getPosition(*getWindow()).x / CELL_SIZE;
				int y = sf::Mouse::getPosition(*getWindow()).y / CELL_SIZE;

				if (m_board.at(convertCoord(x, y)).state != CELL_STATE::OPENED && !m_board.at(convertCoord(x, y)).flagged)
				{
					m_board.at(convertCoord(x, y)).flagged = true;
					m_board.at(convertCoord(x, y)).ChangeTexture("flag", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
				}
				else if (m_board.at(convertCoord(x, y)).flagged)
				{
					m_board.at(convertCoord(x, y)).flagged = false;
					m_board.at(convertCoord(x, y)).ChangeTexture("closed_cell", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(SPRITE_SIZE, SPRITE_SIZE)));
				}
			}
		}
	}

	virtual bool OnUserCreate() override
	{
		// Game is running
		GameOver = false;

		// Setup text
		m_text.setFont(sResourceManager::get().getFont());
		m_text.setFillColor(sf::Color::White);
		m_text.setOutlineColor(sf::Color::Black);
		m_text.setOutlineThickness(5.0f);
		m_text.setCharacterSize(64);
		m_text.setString("Restart");

		//	center text
		sf::FloatRect textRect = m_text.getLocalBounds();
		m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		m_text.setPosition(ScreenWidth() / 2, ScreenHeight() / 2);


		// Create board array
		for (int y = 0; y < ScreenHeight() / CELL_SIZE; y++)
		{
			for (int x = 0; x < ScreenWidth() / CELL_SIZE; x++)
			{
				m_board.push_back(sCell(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE)));
			}
		}

		// Setup random bombs
		int placed_bombs = 0;
		while (placed_bombs != BOMB_COUNT)
		{
			int x = rand() % (ScreenWidth()	/ CELL_SIZE);
			int y = rand() % (ScreenHeight() / CELL_SIZE);

			if (m_board.at(convertCoord(x, y)).state == CELL_STATE::CLOSED)
			{
				m_board.at(convertCoord(x, y)).state = CELL_STATE::BOMB;
				//m_board.at(convertCoord(x, y)).ChangeTexture("bomb", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(CELL_SIZE, CELL_SIZE)));
				placed_bombs++;
			}
		}

		// Setup each cell by checking neighbours
		for (int y = 0; y < ScreenHeight() / CELL_SIZE; y++)
		{
			for (int x = 0; x < ScreenWidth() / CELL_SIZE; x++)
			{
				int Neighbours = 0;

				if (x != 0)
					Neighbours += isBomb(x - 1, y);
				if (y != 0)
					Neighbours += isBomb(x, y - 1);
				if (x != (ScreenWidth() / CELL_SIZE) - 1)
					Neighbours += isBomb(x + 1, y);
				if (y != (ScreenHeight() / CELL_SIZE) - 1)
					Neighbours += isBomb(x, y + 1);
				if (x != 0 && y != 0)
					Neighbours += isBomb(x - 1, y - 1);
				if (x != (ScreenWidth() / CELL_SIZE) - 1 && y != (ScreenHeight() / CELL_SIZE) - 1)
					Neighbours += isBomb(x + 1, y + 1);
				if (x != 0 && y != (ScreenHeight() / CELL_SIZE) - 1)
					Neighbours += isBomb(x - 1, y + 1);
				if (x != (ScreenWidth() / CELL_SIZE) - 1 && y != 0)
					Neighbours += isBomb(x + 1, y - 1);

				m_board.at(convertCoord(x, y)).neighbour_count = Neighbours;
			}
		}

		return true;
	}

	virtual bool OnUserUpdate(sf::Time elapsed) override
	{
		// Draw board
		for (auto &i : m_board)
		{
			Draw(i.sprite);
		}

		if (GameOver)
		{
			Draw(m_text);

			if (m_text.getGlobalBounds().contains(sf::Mouse::getPosition(*getWindow()).x, sf::Mouse::getPosition(*getWindow()).y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// Restart game
				m_board.clear();
				OnUserCreate();
			}
		}

		return true;
	}

};

int main(int argc, char* argv[])
{
	srand(time(0));

	sMineSweeper app;
	app.Construct(640, 640, L"MineSweeper - SFML");
	app.Start();

	return 0;
}