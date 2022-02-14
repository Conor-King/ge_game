#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;

vector<Ship*> ships;

void Load() {
    if (!spritesheet.loadFromFile("res/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(IntRect(Vector2(0, 0), Vector2(32, 32)));


    //Invader* inv = new Invader(IntRect(Vector2(0, 0), Vector2(32, 32)), { 100, 100 });
    //ships.push_back(inv);

    for (int r = 0; r < invaders_rows; ++r) {
        auto rect = IntRect(Vector2(0, 0), Vector2(32, 32)); //Add something here

        for (int c = 0; c < invaders_columns; ++c) {
                Vector2f position =  Vector2f(c * 32 + 16 , r * 32 + 16); // Add something here
                auto inv = new Invader(rect, position);
                ships.push_back(inv);
        }

    }
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
    //window.draw(invader);

    for (const auto s : ships) {
        window.draw(*s);
    }
}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
    Load();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}