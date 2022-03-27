#include "Ghost.h"
#include "system_renderer.h"
#include <iostream>

using namespace sf;
using namespace std;


bool validMove(Vector2f pos) {

	if (pos.x < 0 + 10 || pos.x > 1000 - 10) {
		return false;
	}
	else if (pos.y < 0 + 10 || pos.y > 1000 - 10) {
		return false;
	}
	else {
		return true;
	}
}


void Ghost::Update(double dt) {

	float directX = 0.f;
	float directY = 0.f;
	int newDirection = 0;

	if (moves == 0) {
		newDirection = rand() % 4;
	}
	else if (moves < maxMoves) {
		newDirection = direction;
	}
	else {
		newDirection = rand() % 4;
		moves = 0;
	}

	switch (newDirection) {
	case 0:
		// Left
		direction = 0;
		moves++;
		directX--;
		break;
	case 1:
		// Right
		direction = 1;
		moves++;
		directX++;
		break;
	case 2:
		// Up
		direction = 2;
		moves++;
		directY--;
		break;
	case 3:
		//Down
		direction = 3;
		moves++;
		directY++;
		break;
	default:
		cout << "Problem with switch case.";
		break;
	}

	if (!validMove(getPosition() + Vector2f(directX * 10.f, directY * 10.f))) {
		directX = 0;
		moves = maxMoves;
	}
		

	if (!validMove(getPosition() + Vector2f(directX * 10.f, directY * 10.f))) {
		directY = 0;
		moves = maxMoves;
	}

	move(Vector2f(directX * _speed * dt, directY * _speed * dt));
	Entity::Update(dt);
}

Ghost::Ghost(Color color) : _speed(200.f), Entity(make_unique<CircleShape>(10.f)) {
	_shape->setFillColor(color);
	_shape->setOrigin(Vector2f(10.f, 10.f));
	setPosition(Vector2f(500.f, 500.f));
}

void Ghost::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}
