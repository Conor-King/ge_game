#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Ghost : public Entity {
private:
	float _speed;
	int direction = 0;
	int maxMoves = 5000;
	int moves = 0;


public:
	void Update(double dt) override;
	Ghost(sf::Color color);
	void Render(sf::RenderWindow& window) const override;
};
