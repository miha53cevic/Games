#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.h"
#include "normEnemy.h"
#include "tankEnemy.h"

#include "Bullet.h"

class Spawner
{
public:
	Spawner(sf::Vector2u screen);
	~Spawner() = default;

	void Update(sf::Time elapsed, sf::FloatRect earthRect, std::vector<Bullet>& vecBullets);
	void Draw(sf::RenderWindow *window);

	void addNormEnemy();
	void addTankEnemy();

private:
	std::vector<std::unique_ptr<Enemy>> m_vecEnemies;
	sf::Vector2u m_screenSize;

	sf::Vector2i getRandomPos();
};

