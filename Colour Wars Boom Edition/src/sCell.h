#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "sResourceManager.h"

class sCell
{
public:
	sCell(sf::Vector2f position, std::string texName)
	{
		m_position = position;

		m_spr.setTexture(sResourceManager::get().getTexture(texName));
		m_spr.setPosition(m_position);

		m_block = false;
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

private:
	sf::Sprite		m_spr;
	sf::Vector2f	m_position;

	bool			m_block;
};

