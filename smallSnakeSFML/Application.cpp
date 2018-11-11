#include "Application.h"

Application::Application() : m_window(), m_snake(m_window.getWindowSize(), m_BlockSize), m_world(m_BlockSize, m_window.getWindowSize()) { Setup(); }
Application::Application(sf::Vector2u l_size, std::string l_title) : m_window(l_size, l_title), m_snake(m_window.getWindowSize(), m_BlockSize), m_world(m_BlockSize, m_window.getWindowSize()) { Setup(); }
Application::~Application() {}

void Application::HandleInput()
{
	//HandleInput
	m_snake.HandleInput();
}

void Application::Update()
{
	m_window.Update();

	//Tickrate time control
	float fFrameTime = 1.0f / 5.0f;

	if (m_elapsed.asSeconds() >= fFrameTime)
	{
		m_snake.Update();

		m_elapsed -= sf::seconds(fFrameTime);
	}

	m_world.Update(m_snake);

	if (m_snake.CheckCollision())
	{
		bGameOver = true;
	}
}

void Application::Render()
{
	m_window.BeginDraw(m_backgroundColor);
	
	//Drawing
	m_snake.Draw(m_window.getRenderWindow());
	m_world.Render(m_window.getRenderWindow());

	m_window.EndDraw();
}

void Application::RestartClock()
{
	m_elapsed += m_clock.restart();
}

void Application::Setup()
{
	m_backgroundColor = sf::Color::Black;
	bGameOver = false;
}

void Application::setBackgroundColor(sf::Color l_color) { m_backgroundColor = l_color; }

sf::Time Application::getElapsedTime() { return m_elapsed; }
Window* Application::getWindow() { return &m_window; }
bool Application::GameOver() { return bGameOver; }

