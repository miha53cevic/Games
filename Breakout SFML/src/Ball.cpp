#include "Ball.h"

Ball::Ball(float r)
{
    float DegressAngle = -60;

    m_fAngle = DegressAngle * 3.14159265359 / 180;

    m_DCoord.x = cosf(m_fAngle);
    m_DCoord.y = sinf(m_fAngle);

    m_fSpeed = 200.0f;

    m_ball.setRadius(r);
    m_ball.setOrigin(r, r);
    m_ball.setFillColor(sf::Color::Yellow);

}

void Ball::Update(sf::Time elapsed)
{
    m_ball.move(m_DCoord.x * elapsed.asSeconds() * m_fSpeed, m_DCoord.y * elapsed.asSeconds() * m_fSpeed);
}

void Ball::Draw(sf::RenderWindow *window)
{
    window->draw(m_ball);
}

void Ball::setPos(float x, float y)
{
    m_ball.setPosition(x, y);
}

sf::Vector2f* Ball::getDCoord()
{
    return &m_DCoord;
}

sf::Vector2f Ball::getBallPos()
{
    return m_ball.getPosition();
}

float Ball::getSpeed()
{
    return m_fSpeed;
}

sf::CircleShape Ball::getBallSprite()
{
    return m_ball;
}

