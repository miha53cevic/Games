#include "sEditor.h"

sEditor::sEditor(sf::Vector2u screenSize)
{
	m_mapSize.x = screenSize.x;
	m_mapSize.y = screenSize.y;

	const int m_cellSize = 32;

	for (int y = 0; y < m_mapSize.y / m_cellSize; y++)
	{
		for (int x = 0; x < m_mapSize.x / m_cellSize; x++)
		{
			// Outer walls
			if (y == 0 || x == 0 || y == (m_mapSize.y / m_cellSize) - 1 || x == (m_mapSize.x / m_cellSize) - 1)
				m_map.push_back(sCell(sf::Vector2f(x * m_cellSize, y * m_cellSize), "default_wall"));
			else
				m_map.push_back(sCell(sf::Vector2f(x * m_cellSize, y * m_cellSize), "default_floor"));
		}
	}
}

void sEditor::Update()
{

}

void sEditor::HandleInput()
{

}

void sEditor::Draw(sf::RenderWindow* window)
{
	for (auto &i : m_map)
	{
		i.Draw(window);
	}
}
