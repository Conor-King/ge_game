#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"

using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;

vector<Ship*> ships;

const int gameWidth = 800;
const int gameHeight = 600;

void Load() {
    if (!spritesheet.loadFromFile("res/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(IntRect(Vector2(0, 0), Vector2(32, 32)));


    Invader* inv = new Invader(IntRect(Vector2(0, 0), Vector2(32, 32)), { 100, 100 });
    ships.push_back(inv);
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime.
    static Clock clock;
    float dt = clock.restart().asSeconds();

    for (auto& s : ships) {
        s->Update(dt);
    }
}

void Render(RenderWindow& window) {
    window.draw(invader);

    for (const auto s : ships) {
        window.draw(*s);
    }
}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}