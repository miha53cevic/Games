#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
public:
    Bird();

    void Move                   (float x, float y           );
    void SetPosition            (float x, float y           );
    void Rotate                 (int angle                  );
    void Draw                   (sf::RenderWindow& window   );

    sf::Vector2f GetPosition    ();

    bool isColliding            (sf::FloatRect rect);

private:
    sf::Sprite m_sprite;
};