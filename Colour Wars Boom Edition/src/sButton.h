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
		m_button.setSize(sf::Vector2f(fontSize * line.size(), fontSize * 1.5f));

		m_button.setOutlineColor(sf::Color::Black);
		m_button.setOutlineThickness(1.0f);

		// Setup text
		m_text.setFont(sResourceManager::get().getFont());
		m_text.setCharacterSize(fontSize);
		m_text.setPosition(pos);
		m_text.setString(line);

		// Visible by default
		m_visible = true;
	}

	void Draw(sf::RenderWindow* window)
	{
		if (m_visible)
		{
			window->draw(m_button);
			window->draw(m_text);
		}
	}

	bool isClicked(sf::RenderWindow* window)
	{
		// If the button is invisible return false
		if (!m_visible)
			return false;

		if (m_button.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return true;
		}
		else return false;
	}

	void setVisible(bool visibility) { m_visible = visibility; }
	bool isVisible() { return m_visible; }

	std::string getString() { return m_text.getString(); }
	int getCharSize() { return m_text.getCharacterSize(); }

private:
	sf::RectangleShape	m_button;
	sf::Text			m_text;

	bool				m_visible;
};