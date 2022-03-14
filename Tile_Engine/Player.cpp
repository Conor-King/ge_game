#include "Player.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;

bool validMove(Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

void Player::Update(double dt) {

	float directY = 0.f;
	float directX = 0.f;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		directY--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		directY++;
	}
	if (!validMove(getPosition() + Vector2f(directX * 25.f, directY * 25.f)))
		directY = 0;

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		directX--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		directX++;
	}

	if (!validMove(getPosition() + Vector2f(directX * 25.f, directY * 25.f)))
		directX = 0;

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