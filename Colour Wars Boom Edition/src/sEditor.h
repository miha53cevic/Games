#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "sCell.h"
#include "sButton.h"

#include "ToggleKey.h"
#include "Util.h"

class sEditor
{
public:
	sEditor(sf::Vector2u screenSize);

	void Update(sf::RenderWindow* window);
	void HandleInput(sf::RenderWindow& window);
	void Draw(sf::RenderWindow* window);

	void Save(std::string mapName);
	void Load(std::string mapName);

private:	
	std::vector<sCell> m_map;

	std::string m_selectedType;

	std::vector<sButton> m_UI;

	bool m_selecting;

	sf::Vector2i m_mapSize;

	ToggleKey m_toolbarKey;
};

