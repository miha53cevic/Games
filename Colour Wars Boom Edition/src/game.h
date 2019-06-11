#pragma once
#include "window.h"
#include "sEditor.h"

class Game
{
public:
	Game(const sf::Vector2u& l_size, const std::string& l_name);
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* getWindow();

	void RestartClock();

private:
	Window m_window;

	sEditor m_editor;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};