#pragma once
#include "Window.h"
#include "Snake.h"
#include "World.h"

const int m_BlockSize = 16;

class Application
{
public:
	Application();
	Application(sf::Vector2u l_size, std::string l_title);
	~Application();

	void HandleInput();
	void Update();
	void Render();

	void RestartClock();

	void setBackgroundColor(sf::Color l_color);
	
	sf::Time getElapsedTime();

	Window* getWindow();

	bool GameOver();

private:
	Window m_window;
	Snake m_snake;
	World m_world;

	sf::Color m_backgroundColor;
	
	sf::Clock m_clock;
	sf::Time m_elapsed;

	bool bGameOver;

	void Setup();
};

