#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Vector2u screen)
{
	m_screenSize.x = screen.x;
	m_screenSize.y = screen.y;

	m_enemy.setOrigin(m_enemyTex.getSize().x / 2, m_enemyTex.getSize().y / 2);
	m_enemy.setPosition(x, y);

	Vector2<float> vecA = VectorMath::getVector(x, y, (float)screen.x / 2, (float)screen.y / 2);
	vecA = VectorMath::NormalizeVector(vecA);

	m_velocity.x = vecA.x;
	m_velocity.y = vecA.y;

	m_HP = 1;
}

void Enemy::Draw(sf::RenderWindow *window)
{
	window->draw(m_enemy);
}

void Enemy::Update(sf::Time elapsed, float fSpeed)
{
	m_enemy.move(m_velocity.x * elapsed.asSeconds() * fSpeed, m_velocity.y * elapsed.asSeconds() * fSpeed);
	m_enemy.rotate(1.0f);
}

sf::FloatRect Enemy::getEnemyRect()
{
	sf::FloatRect enemy = m_enemy.getGlobalBounds();
	return enemy;
}

int Enemy::getHP()
{
	return m_HP;
}

void Enemy::RemoveHP(int HP)
{
	m_HP -= HP;
}
