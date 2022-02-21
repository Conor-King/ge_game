#include "bullet.h";
#include "game.h"
#include "ship.h"
	
using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];

Bullet::Bullet() {}

void Bullet::Init() {

	for (auto &b : bullets) {
		b.setPosition(Vector2f(-100, -100));
		b.setTexture(spritesheet);
		b.setTextureRect(IntRect(Vector2(32, 32), Vector2(32, 32)));
		b.setOrigin(Vector2f(0.f, 0.f));
	}
}

void Bullet::Fire(const Vector2f &pos, bool mode) {

	bulletPointer++;
	bullets[bulletPointer]._mode = mode;
	bullets[bulletPointer].setPosition(pos);
}

void Bullet::Render(RenderWindow &window) {

	/*if (selectedBullet._mode == false) {
		selectedBullet.setTextureRect(IntRect(Vector2(64, 32), Vector2(32, 32)));
	}*/

	for (const auto b : bullets)
	{
		window.draw(b);
	}
}

void Bullet::Update(const float &dt) {
	for (auto &b : bullets) {
		b._Update(dt);
	}
}

void Bullet::_Update(const float& dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		return;
	
	}
	else {
		move(Vector2f(0, dt * 200.f * (_mode ? 1.0f : -1.0f)));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s->isplayer == true) {
				continue;
			}
			
			if (_mode && s->isplayer == false) {
				continue;
			}

			if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
				s->Explode();
				setPosition(Vector2f(-100, -100));
				return;
			}
		}
	}
}

// Can't see if the bullets are actually working since they don't show up in the game.
// Getting an error every time the program starts.

