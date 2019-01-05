#include "game.h"

Game::Game()
	: m_world(m_window.getSize())
	, m_player(m_window.getSize())
	, m_spawner(m_window.getSize())
{
	//Load Default settings && Textures
}
Game::Game(const sf::Vector2u& l_size, const std::string& l_name)
	: m_window(l_size, l_name)
	, m_world(m_window.getSize())
	, m_player(m_window.getSize())
	, m_spawner(m_window.getSize())
	{}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::HandleInput()
{
	//input
	m_player.Input();
}

void Game::Update()
{
	//Event System
	m_window.Update();

	m_world.Update();
	m_player.Update(m_elapsed);
	m_spawner.Update(m_elapsed, m_world.getEarthRect(), m_player.getBulletVector());
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::White);
	
	m_world.Draw(m_window.getWindow());
	m_player.Draw(m_window.getWindow());
	m_spawner.Draw(m_window.getWindow());

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}