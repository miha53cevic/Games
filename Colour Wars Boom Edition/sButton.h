#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "sResourceManager.h"

class sButton
{
public:
	sButton(sf::Vector2f pos, float fontSize, std::string line, sf::Color c)
	{
		m_button.setFillColor(c);
		m_button.setPosition(pos);
		m_button.setSize(sf::Vector2f(fontSize * line.size(), fontSize));

		m_button.setOutlineColor(sf::Color::Black);
		m_button.setOutlineThickness(1.0f);

		// Setup text
		m_text.setFont(sResourceManager::get().getFont());
		m_text.setCharacterSize(fontSize);
		m_text.setPosition(pos);
		m_text.setString(line);
	}

	void Draw(sf::RenderWindow* window)
	{
		window->draw(m_button);
		window->draw(m_text);
	}

	bool isClicked(sf::RenderWindow* window)
	{
		if (m_button.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return true;
		}
		else return false;
	}

	std::string getString() { return m_text.getString(); }

private:
	sf::RectangleShape	m_button;
	sf::Text			m_text;
};