#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "sCell.h"

class sEditor
{
public:
	sEditor(sf::Vector2u screenSize);

	void Update();
	void HandleInput();
	void Draw(sf::RenderWindow* window);

private:	
	std::vector<sCell> m_map;

	sf::Vector2i m_mapSize;
};

