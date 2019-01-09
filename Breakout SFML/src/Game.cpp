#include "Game.h"

Game::Game(sf::Vector2u l_size, std::string l_name)
    : m_window(l_size, l_name)
    , m_world(m_window.getSize())
    , m_player(m_window.getSize())
{}

void Game::HandleInput()
{
    // handle input
    m_player.HandleInput(m_elapsed, m_world.getBlockSize().x);
}

void Game::Update()
{
    // Updates
    m_window.Update();

    m_world.Update(m_elapsed);
    m_player.Update(m_world.getBall());
}

void Game::Render()
{
    m_window.BeginDraw();

    // Draw
    m_world.Draw(m_window.getRenderWindow());
    m_player.Draw(m_window.getRenderWindow());

    m_window.EndDraw();
}

void Game::getElapsedTime()
{
    m_elapsed = m_clock.restart();
}

Window* Game::getWindow()
{
    return &m_window;
}
