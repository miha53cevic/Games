#include "Bird.h"
#include "../ResourceManager/ResourceManager.h"

Bird::Bird()
{
    // Setup bird sprite
    m_sprite.setTexture(ResourceManager::get().getTexture("sprite_sheet"));
    m_sprite.setTextureRect({0, 0, 64, 64});
    m_sprite.setScale(0.5f, 0.5f);
    m_sprite.setOrigin({ 32, 32 });
}

void Bird::SetPosition(float x, float y)    { m_sprite.setPosition(x, y);       }
void Bird::Move(float x, float y)           { m_sprite.move(x, y);              }
void Bird::Rotate(int angle)                { m_sprite.rotate(angle);           }
void Bird::Draw(sf::RenderWindow& window)   { window.draw(m_sprite);            }

sf::Vector2f Bird::GetPosition()            { return m_sprite.getPosition();    }

bool Bird::isColliding(sf::FloatRect rect)
{
    return m_sprite.getGlobalBounds().intersects(rect);
}