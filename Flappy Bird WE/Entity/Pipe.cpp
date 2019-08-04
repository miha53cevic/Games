#include "Pipe.h"
#include "../defines.h"
#include "../Utility.h"

Pipe::Pipe(sf::Vector2i screen)
    : m_screen(screen)
{
    // Load texture
    m_sprite[0].setTexture(ResourceManager::get().getTexture("sprite_sheet"));
    m_sprite[1].setTexture(ResourceManager::get().getTexture("sprite_sheet"));


    CreatePipe();
}

void Pipe::Draw(sf::RenderWindow &window)
{
    for (int i = 0; i < 2; i++)
    {
        window.draw(m_sprite[i]);
    }
}

void Pipe::Update(float deltaTime)
{
    // Speed = SCROLLING_SPEED * deltaTime
    for (int i = 0; i < 2; i++)
    {
        m_sprite[i].move(-deltaTime * SCROLL_SPEED, 0);
    }

    // Check if pipe has left the screen
    if (getPosition().x + 64 < 0)
    {
        CreatePipe();
    }
}

void Pipe::CreatePipe()
{
    // Calculate lower pipe
    // Note: Minimalni size doljneg pipe-a je 64
    m_pipeSize = iRandom(64, (((m_screen.y - GROUND_HEIGHT) - (64 * 2 + SPACE_HEIGHT)) + 1));

    m_sprite[0].setTextureRect({ 896, 0, 64, m_pipeSize });
    m_sprite[0].setPosition(m_screen.x, (m_screen.y - GROUND_HEIGHT) - m_pipeSize);

    // Calculate upper pipe
    m_sprite[1].setTextureRect({ 960, 384 - ((m_screen.y - GROUND_HEIGHT) - (m_pipeSize + SPACE_HEIGHT)), 64, ((m_screen.y - GROUND_HEIGHT) - (m_pipeSize + SPACE_HEIGHT)) }); //Komplicirana i glupa formula
	m_sprite[1].setPosition(m_screen.x, 0);
}

sf::Vector2f Pipe::getPosition()
{
    return m_sprite[0].getPosition();
}

sf::Sprite& Pipe::getLowerPipe()
{
    return m_sprite[0];
}

sf::Sprite& Pipe::getUpperPipe()
{
    return m_sprite[1];
}