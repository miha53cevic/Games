#include "World.h"

#include <iostream>

World::World(sf::Vector2u l_size)
    : m_winSize(l_size)
    , m_ball(5.0f)
    , m_textbox(l_size.x / 2, l_size.y / 3)
{
    Setup();
}

void World::Update(sf::Time elapsed)
{
    // Ball Collision
    int CellX = m_ball.getBallPos().x / m_blockSize.x;
    int CellY = m_ball.getBallPos().y / m_blockSize.y;

    int NewCellX = (m_ball.getBallPos().x + m_ball.getDCoord()->x * elapsed.asSeconds() * m_ball.getSpeed()) / m_blockSize.x;
    int NewCellY = (m_ball.getBallPos().y + m_ball.getDCoord()->y * elapsed.asSeconds() * m_ball.getSpeed()) / m_blockSize.y;

    if (m_map[(NewCellY * m_mapSize.x) + NewCellX] == '#')
    {
        if (NewCellX != CellX)
        {
            m_ball.getDCoord()->x *= -1.0f;
        }
        if (NewCellY != CellY)
        {
            m_ball.getDCoord()->y *= -1.0f;
        }

        std::cout << "X = " << m_ball.getDCoord()->x << " Y =" << m_ball.getDCoord()->y << "\n";
    }
    else if (m_map[(NewCellY * m_mapSize.x) + NewCellX] == '1')
    {
        if (NewCellX != CellX)
        {
            m_ball.getDCoord()->x *= -1.0f;
        }
        if (NewCellY != CellY)
        {
            m_ball.getDCoord()->y *= -1.0f;
        }

        // Remove it from the map
        m_map[(NewCellY * m_mapSize.x) + NewCellX] = '.';

        // Add to score
        m_score++;
    }

    // Update / Move Ball
    m_ball.Update(elapsed);

    // Check if ball is out of map
    if (m_ball.getBallPos().y > m_winSize.y)
    {
        // Remove 1 ball from BallsLeft
        m_BallsLeft--;

        // Reset Pos
        m_ball.setPos(m_winSize.x / 2, m_winSize.y / 2);
    }

    // Update TextBox
    m_textbox.setString(std::to_string(m_score));
}

void World::Draw(sf::RenderWindow *window)
{
    for (int y = 0; y < m_mapSize.y; y++)
    {
        for (int x = 0; x < m_mapSize.x; x++)
        {
            switch(m_map[(y * m_mapSize.x) + x])
            {
            case '#':
                {
                    // Draw Walls
                    m_block.setFillColor(sf::Color(125, 125, 125));
                    m_block.setPosition(x * m_blockSize.x, y * m_blockSize.y);
                    window->draw(m_block);

                     break;
                }
            case '1':
                {
                    // Draw Tiles
                    m_block.setFillColor(sf::Color::Green);
                    m_block.setPosition(x * m_blockSize.x, y * m_blockSize.y);
                    window->draw(m_block);

                    break;
                }
            }
        }
    }

    // Draw Ball
    m_ball.Draw(window);

    // Draw TextBox
    m_textbox.Draw(window);
}

sf::Vector2i World::getBlockSize()
{
    return m_blockSize;
}

Ball* World::getBall()
{
    return &m_ball;
}

void World::Setup()
{
    // Setup Map
    m_mapSize.x = 32;
    m_mapSize.y = 32;

    m_blockSize.x = (int)m_winSize.x / m_mapSize.x;
    m_blockSize.y = (int)m_winSize.y / m_mapSize.y;

    m_map += "################################";
    m_map += "#..............................#";
    m_map += "#....11111111111111111111111...#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";
    m_map += "#..............................#";

    // Setup Building Block
    m_block.setFillColor(sf::Color(125, 125, 125));
    m_block.setSize(sf::Vector2f(m_blockSize.x, m_blockSize.y));

    m_ball.setPos(m_winSize.x / 2, m_winSize.y / 2);

    // Reset score and life counters
    m_score     = 0;
    m_BallsLeft = 3;
}
