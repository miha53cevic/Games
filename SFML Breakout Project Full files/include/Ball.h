#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <math.h>

class Ball
{
    public:
        Ball(float r);
        ~Ball() = default;

        void Update(sf::Time elapsed);
        void Draw(sf::RenderWindow *window);

        void setPos(float x, float y);

        sf::Vector2f* getDCoord();
        sf::Vector2f getBallPos();
        float getSpeed();
        sf::CircleShape getBallSprite();

    private:
        sf::CircleShape m_ball;
        float m_fAngle;

        sf::Vector2f m_DCoord;

        float m_fSpeed;
};

#endif // BALL_H
