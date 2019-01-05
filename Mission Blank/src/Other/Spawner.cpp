#include "Spawner.h"

Spawner::Spawner(sf::Vector2u screen)
{
	m_screenSize = screen;
}

void Spawner::Update(sf::Time elapsed, sf::FloatRect earthRect, std::vector<Bullet>& vecBullets)
{
	if (!m_vecEnemies.empty())
	{
		for (auto &i : m_vecEnemies)
		{
			i->Update(elapsed);
		}
	}

	// Add Enemies
	if (m_vecEnemies.size() < 5)
	{
		addNormEnemy();

		if (rand() % 256 >= 200)
		{
			addTankEnemy();
		}
	}

	//Check for collision with earth
	std::vector<std::unique_ptr<Enemy>>::iterator iter;
	sf::FloatRect earth = earthRect;

	for (iter = m_vecEnemies.begin(); iter != m_vecEnemies.end(); )
	{
		if ((*iter)->getEnemyRect().intersects(earthRect))
		{
			iter = m_vecEnemies.erase(iter);
		}
		else iter++;
	}

	//Check for bullet collision
	std::vector<Bullet>::iterator bulletIter;

	for (iter = m_vecEnemies.begin(); iter != m_vecEnemies.end();)
	{
		bool Collision = false;

		sf::FloatRect enemy = (*iter)->getEnemyRect();

		for (bulletIter = vecBullets.begin(); bulletIter != vecBullets.end();)
		{
			sf::FloatRect bullet = bulletIter->getBullet()->getGlobalBounds();

			if (bullet.intersects(enemy))
			{
				// Remove HP
				(*iter)->RemoveHP(bulletIter->getDamage());

				// Check if HP is lower or EQUAL to 0
				if ((*iter)->getHP() <= 0)
				{

					//Delete Enemy
					iter = m_vecEnemies.erase(iter);
				}

				//Delete Bullet
				bulletIter = vecBullets.erase(bulletIter);

				Collision = true;
			}
			else
			{
				bulletIter++;
			}
		}
		if (!Collision)
		{
			iter++;
		}
	}
}

void Spawner::Draw(sf::RenderWindow *window)
{
	if (!m_vecEnemies.empty())
	{
		for (auto &i : m_vecEnemies)
		{
			i->Draw(window);
		}
	}
}

void Spawner::addNormEnemy()
{
	m_vecEnemies.push_back(std::unique_ptr<Enemy>(new normEnemy(getRandomPos().x, getRandomPos().y, m_screenSize)));
}

void Spawner::addTankEnemy()
{
	m_vecEnemies.push_back(std::unique_ptr<Enemy>(new tankEnemy(getRandomPos().x, getRandomPos().y, m_screenSize)));
}

sf::Vector2i Spawner::getRandomPos()
{
	int x = rand() % m_screenSize.x;
	int y = rand() % m_screenSize.y;

	if (x <= (int)m_screenSize.x / 2)
	{
		x -= (int)m_screenSize.x / 2;
	}
	else if (x > (int)m_screenSize.x / 2)
	{
		x += (int)m_screenSize.x / 2;
	}

	if (y <= (int)m_screenSize.y / 2)
	{
		y -= (int)m_screenSize.y / 2;
	}
	else if (y > (int)m_screenSize.y / 2)
	{
		y += (int)m_screenSize.y / 2;
	}

	return sf::Vector2i(x, y);
}


