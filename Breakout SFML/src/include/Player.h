#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include <Ball.h>

class Player
{
    public:
        Player(sf::Vector2u l_size);
        ~Player() = default;

        void HandleInput(sf::Time elapsed, int blockSizeX);
        void Update(Ball* ball);
        void Draw(sf::RenderWindow *window);

    private:
    sf::RectangleShape m_player;

    sf::Vector2f m_winSize;

    float m_fSpeed;
};

#endif // PLAYER_H
