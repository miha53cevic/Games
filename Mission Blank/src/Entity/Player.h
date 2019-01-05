#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "Math.h"
#include "VectorMath.h"
#include "Bullet.h"
#include "ToggleKey.h"

class Player
{
public:
	Player(sf::Vector2u screen);
	~Player() = default;

	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow *window);
	void Input();

	std::vector<Bullet>& getBulletVector();

private:
	sf::Sprite m_player;
	sf::Texture m_playerTex;

	sf::Vector2u m_screenSize;

	int m_distanceFromPlanet;
	float m_angle;

	void UpdatePosition();

	std::vector<Bullet> m_vecBullets;

	ToggleKey m_shoot;
};

