#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(float x, float y, float r = 16.0f, sf::Color c = sf::Color::Red)
	{
		bullet.setRadius(r);
		bullet.setOrigin(sf::Vector2f(r / 2, r / 2));
		bullet.setFillColor(c);
		bullet.setPosition(x, y);

		Damage = 1;
	}

	sf::CircleShape* getBullet()
	{
		return &bullet;
	}

	void setVelocity(sf::Vector2f velocity)
	{
		fVelocity.x = velocity.x;
		fVelocity.y = velocity.y;
	}

	void Draw(sf::RenderWindow *window)
	{
		window->draw(bullet);
	}

	void Update(sf::Time Elapsed, float fSpeed = 100.0f)
	{
		bullet.move(fVelocity.x * fSpeed * Elapsed.asSeconds(), fVelocity.y * fSpeed * Elapsed.asSeconds());
	}

	void setDamage(int damage)
	{
		Damage = damage;
	}

	int getDamage()
	{
		return Damage;
	}

private:
	sf::CircleShape bullet;

	sf::Vector2f fVelocity;

	int Damage;
};
