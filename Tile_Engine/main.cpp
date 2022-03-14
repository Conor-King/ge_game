#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"
#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

unique_ptr<Player> player(new Player);

void Load() {

    ls::loadLevelFile("res/levels/maze.txt");

    // print the level to the console
    for (size_t y = 0; y < ls::getHeight(); y++) {
        for (size_t x = 0; x < ls::getWidth(); x++) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }

    
}

void Update(RenderWindow& window) {
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // Check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    // Quit via ESC key.
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }
    
    player->Update(dt);
}

void Render(RenderWindow& window) {
    // Draw everything
    ls::Render(window);
    player->Render(window);
}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}