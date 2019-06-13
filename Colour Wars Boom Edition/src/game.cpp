#include "game.h"

Game::Game(const sf::Vector2u& l_size, const std::string& l_name)
	: m_window(l_size, l_name)
	, m_editor(m_window.getSize())
{}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::HandleInput()
{
	//input
	m_editor.HandleInput(*m_window.getWindow());
}

void Game::Update()
{
	//Event System
	m_window.Update();
	m_editor.Update(m_window.getWindow());
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::White);

	m_editor.Draw(m_window.getWindow());
	
	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}