#pragma once
#include <SFML/Graphics.hpp>
#include "../ResourceManager/ResourceManager.h"

class Pipe
{
public:
    Pipe(sf::Vector2i screen);

    void Draw           (sf::RenderWindow &window   );
    void Update         (float deltaTime            );
    void CreatePipe     (                           );

    sf::Vector2f getPosition();

    sf::Sprite& getUpperPipe();
    sf::Sprite& getLowerPipe();

private:
    sf::Sprite      m_sprite[2];
    sf::Vector2i    m_screen;

    int             m_pipeSize;
};