#pragma once
#include "Enemy.h"
class tankEnemy : public Enemy
{
public:
	tankEnemy(float x, float y, sf::Vector2u screen);
	~tankEnemy() = default;

private:
};

