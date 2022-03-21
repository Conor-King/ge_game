#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Ghost.h"
#include "Player.h"

using namespace sf;
using namespace std;

int gameWidth = 1000;
int gameHeight = 1000;

vector<Entity*> entityList;

void Load() {
    
    // Creating the ghosts in the game and assigning colors.
    for (int i = 0; i < 4; i++)
    {
        Color colors[4] = { Color::Red, Color::Blue, Color::Green, Color::Magenta };

        auto ghost = new Ghost(colors[i + 1]);

        entityList.push_back(ghost);
    }

    Player* player(new Player);
    entityList.push_back(player);
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime.
    static Clock clock;
    float dt = clock.restart().asSeconds();

    for (auto& e : entityList) {
        e->Update(dt);
    }
}

void Render(RenderWindow& window) {
    for (auto& e : entityList) {
        e->Render(window);
    }
}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "Pacman");
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