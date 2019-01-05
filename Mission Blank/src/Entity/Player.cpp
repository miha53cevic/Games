#include "Player.h"

Player::Player(sf::Vector2u screen)
	: m_shoot(sf::Keyboard::Key::Space, 0.5f)
{
	m_screenSize = screen;

	m_distanceFromPlanet = 100;
	m_angle = 0.0f;

	//Load Player
	if (!m_playerTex.loadFromFile("tex/player.png"))
	{
		// Error
	}
	else
	{
		m_player.setTexture(m_playerTex);
		m_player.setOrigin(m_playerTex.getSize().x / 2, 0);
		m_player.rotate(90.0f);

		UpdatePosition();
	}
}

void Player::UpdatePosition()
{
	float x = std::cosf(Math::DegressToRadians(m_angle)) * m_distanceFromPlanet + m_screenSize.x / 2;
	float y = std::sinf(Math::DegressToRadians(m_angle)) * m_distanceFromPlanet + m_screenSize.y / 2;

	m_player.setPosition(sf::Vector2f(x, y));
}


void Player::Update(sf::Time elapsed)
{
	if (!m_vecBullets.empty())
	{
		// Update bullets
		for (auto &i : m_vecBullets)
		{
			i.Update(elapsed, 200.0f);
		}

		// Check if bullet out of bounds
		std::vector<Bullet>::iterator iter;
		for (iter = m_vecBullets.begin(); iter != m_vecBullets.end(); )
		{
			if (iter->getBullet()->getPosition().x < 0 || iter->getBullet()->getPosition().y < 0 || iter->getBullet()->getPosition().x >= m_screenSize.x || iter->getBullet()->getPosition().y >= m_screenSize.y)
			{
				iter = m_vecBullets.erase(iter);
			}
			else iter++;
		}
	}
}

void Player::Draw(sf::RenderWindow *window)
{
	// Draw Player
	window->draw(m_player);

	if (!m_vecBullets.empty())
	{
		// Draw Bullets
		for (auto &i : m_vecBullets)
		{
			i.Draw(window);
		}
	}
}

void Player::Input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_angle -= 2.0f;
		m_player.rotate(-2.0f);

		UpdatePosition();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_angle += 2.0f;
		m_player.rotate(+2.0f);

		UpdatePosition();
	}

	// Shooting
	if (m_shoot.isKeyPressed())
	{
		Bullet newBullet(m_player.getPosition().x, m_player.getPosition().y, 5.0f);
		
		Vector2<float> vecA;
		vecA = VectorMath::getVector((float)m_screenSize.x / 2, (float)m_screenSize.y / 2, m_player.getPosition().x, m_player.getPosition().y);
		vecA = VectorMath::NormalizeVector(vecA);

		sf::Vector2f velocity;
		velocity.x = vecA.x;
		velocity.y = vecA.y;

		newBullet.setVelocity(velocity);

		m_vecBullets.push_back(newBullet);
	}
}

std::vector<Bullet>& Player::getBulletVector()
{
	return m_vecBullets;
}