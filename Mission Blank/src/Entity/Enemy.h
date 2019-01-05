#pragma once
#include <SFML/Graphics.hpp>
#include "VectorMath.h"

class Enemy
{
public:
	Enemy(float x, float y, sf::Vector2u screen);
	~Enemy() = default;

	virtual void Update(sf::Time elapsed, float fSpeed = 100.0f);
	virtual void Draw(sf::RenderWindow *window);

	sf::FloatRect getEnemyRect();
	int getHP();

	void RemoveHP(int HP);

protected:
	sf::Vector2f m_velocity;

	sf::Sprite m_enemy;
	sf::Texture m_enemyTex;

	void setVelocity(sf::Vector2f velocity)
	{
		m_velocity.x = velocity.x;
		m_velocity.y = velocity.y;
	}

	void setVelocity(Vector2<float> velocity)
	{
		m_velocity.x = velocity.x;
		m_velocity.y = velocity.y;
	}

	int m_HP;

private:
	sf::Vector2u m_screenSize;
};

