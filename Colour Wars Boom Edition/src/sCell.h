#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "sResourceManager.h"

// Global because all cell textures should be 32x32
const int CELL_SIZE = 32;

class sCell
{
public:
	sCell(sf::Vector2f position, std::string texName)
	{
		m_position = position;

		m_spr.setTexture(sResourceManager::get().getTexture(texName));
		m_spr.setPosition(m_position);

		m_block		= false;
		m_tex_name	= texName;
	}

	void setBlocking(bool choice)
	{
		m_block = choice;
	}

	bool isBlocking()
	{
		return m_block;
	}

	void Draw(sf::RenderWindow* window)
	{
		window->draw(m_spr);
	}

	void ChangeTexture(std::string texName)
	{
		m_spr.setTexture(sResourceManager::get().getTexture(texName));
		m_tex_name = texName;
	}

	sf::Vector2f &getPosition() { return m_position; }
	std::string getTexName() { return m_tex_name; }

private:
	sf::Sprite		m_spr;
	sf::Vector2f	m_position;

	std::string		m_tex_name;

	bool			m_block;
};

