#pragma once
#include <SFML/Graphics.hpp>

class Ground
{
public:
    Ground();

    void Draw           (sf::RenderWindow& window   );
    void Update         (float deltaTime            );
    void setPosition    (float x, float y           );

    sf::Vector2f   getPosition ();
    sf::Sprite&    getSprite   ();

private:
    sf::Sprite m_sprite;
};