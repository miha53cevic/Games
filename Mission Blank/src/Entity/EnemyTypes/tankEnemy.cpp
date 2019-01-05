#include "tankEnemy.h"

tankEnemy::tankEnemy(float x, float y, sf::Vector2u screen)
	: Enemy(x, y, screen)
{
	// Load Sprite
	if (!m_enemyTex.loadFromFile("tex/tankEnemy.png"))
	{
		// Error
	}
	else
	{
		m_enemy.setTexture(m_enemyTex);
	}

	m_HP = 3;
}

