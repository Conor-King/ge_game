#include "Player.h"

using namespace sf;
using namespace std;

void Player::Update(double dt) {

	float directY = 0.f;
	float directX = 0.f;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		directY--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		directY++;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		directX--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		directX++;
	}
	move(Vector2f(directX * _speed * dt, directY * _speed * dt));

	Entity::Update(dt);
}

Player::Player() : _speed(200.f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}