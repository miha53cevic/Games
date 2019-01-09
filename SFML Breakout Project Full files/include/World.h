#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "Ball.h"
#include "TextBox.h"

class World
{
public:
    World(sf::Vector2u l_size);
    ~World() = default;

    void Update(sf::Time elapsed);
    void Draw(sf::RenderWindow* window);

    sf::Vector2i getBlockSize();
    Ball* getBall();

private:
    std::string m_map;

    sf::Vector2i m_mapSize;
    sf::Vector2i m_blockSize;

    sf::Vector2u m_winSize;

    sf::RectangleShape m_block;

    TextBox m_textbox;

    int m_score;
    int m_BallsLeft;

    Ball m_ball;

    void Setup();
};

#endif // WORLD_H
