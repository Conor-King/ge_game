//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir, bool player) : Sprite() {
  _sprite = ir;
  isplayer = player;
  setTexture(spritesheet);
  setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

void Ship::Explode() {
    setTextureRect(IntRect(Vector2(128, 32), Vector2(32, 32)));
    _exploded = true;
}

bool Ship::is_exploded() const{
    return _exploded;
}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

Invader::Invader() : Ship() {}

bool Invader::direction;
float Invader::speed = 50; // Ships speed here.

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir, false) {
    setOrigin(Vector2f(0.f, 0.f));;
    setPosition(pos);
}

void Invader::Update(const float& dt) {
    Ship::Update(dt);

    move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

    if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size(); ++i) {
            if (ships[i]->isplayer == false) {
                ships[i]->move(Vector2f(0.0f, 24.0f));
            }
        }
    }
}

Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32)), true) {
    setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
    Ship::Update(dt);
    static vector<Bullet*> bullets;

    float playerDirection = 0.f;
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        // Move left
        playerDirection--;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        // Move right
        playerDirection++;
    }
    move(Vector2f(playerDirection * 100.f * dt, 0.f));

    if (Keyboard::isKeyPressed(Keyboard::F)) {
        Bullet::Fire(getPosition(), false);
    }
    
}