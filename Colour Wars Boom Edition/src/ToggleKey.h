#pragma once
#include <SFML/Graphics.hpp>

class ToggleKey
{
public:
	ToggleKey(sf::Keyboard::Key l_key, float l_fTimeDelay = 0.2f)
		: m_key(l_key)
		, m_fTimeDelay(l_fTimeDelay)
	{}

	// If the key is pressed get the time that has elapsed
	// since the last time the key was pressed if it is
	// longer than fTimeDelay then restart and return true
	bool isKeyPressed()
	{
		if (sf::Keyboard::isKeyPressed(m_key)) {
			if (m_delay.getElapsedTime().asSeconds() > m_fTimeDelay) {

				m_delay.restart();
				return true;
			}
		}
		return false;
	}

private:
	sf::Keyboard::Key m_key;
	sf::Clock m_delay;

	float m_fTimeDelay;
};