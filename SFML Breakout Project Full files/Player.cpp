#include "Player.h"

Player::Player(sf::Vector2u l_size)
    : m_winSize(l_size)
{
    m_fSpeed = 200.0f;

    // Player Rect Settings
    m_player.setFillColor(sf::Color::White);
    m_player.setSize(sf::Vector2f(50, 5));

    // Set player to middle of the screen
    m_player.setPosition(l_size.x / 2, l_size.y - m_player.getSize().y);
}

void Player::HandleInput(sf::Time elapsed, int blockSizeX)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (m_player.getPosition().x >= blockSizeX)
            m_player.move(-m_fSpeed * elapsed.asSeconds(), 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (m_player.getPosition().x + m_player.getSize().x <= (int)m_winSize.x - blockSizeX)
            m_player.move(+m_fSpeed * elapsed.asSeconds(), 0);
    }
}

void Player::Update(Ball* ball)
{
    // Ball & Player Collision
    sf::FloatRect playerRect = m_player.getGlobalBounds();
    sf::FloatRect ballRect = ball->getBallSprite().getGlobalBounds();

    if (playerRect.intersects(ballRect))
    {
        ball->getDCoord()->y *= -1;
    }
}

void Player::Draw(sf::RenderWindow *window)
{
    window->draw(m_player);
}
