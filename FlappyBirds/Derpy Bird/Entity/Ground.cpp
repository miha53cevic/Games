#include "Ground.h"
#include "../ResourceManager/ResourceManager.h"
#include "../defines.h"

Ground::Ground()
{
    m_sprite.setTexture(ResourceManager::get().getTexture("sprite_sheet"));
    m_sprite.setTextureRect({ 0, 64, 640, 128 });
    m_sprite.setOrigin({ 0, 128 });
}

void Ground::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Ground::Update(float deltaTime)
{
    m_sprite.move(-SCROLL_SPEED * deltaTime, 0);
}

void Ground::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::Vector2f Ground::getPosition()
{
    return m_sprite.getPosition();
}

sf::Sprite& Ground::getSprite()
{
    return m_sprite;
}