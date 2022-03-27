#include "entity.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }

void Entity::setPosition(const Vector2f& pos) { _position = pos; }

void Entity::move(const Vector2f& pos) { _position += pos; }

void Entity::Update(const double dt) {
    _shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

void EntityManager::Render(RenderWindow& window) {
	for each (auto ent in list)
	{
		ent->Render(window);
	}
}

void EntityManager::Update(double dt) {
	for each (auto ent in list)
	{
		ent->Update(dt);
	}
}