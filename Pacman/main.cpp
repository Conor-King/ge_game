#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Ghost.h"
#include "Player.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

int gameWidth = 1000;
int gameHeight = 1000;

EntityManager em;

vector<Entity*> entityList;

void Load() {
    
    // Creating the ghosts in the game and assigning colors.
    for (int i = 1; i < 5; i++)
    {
        Color colors[4] = { Color::Red, Color::Blue, Color::Green, Color::Magenta};

        shared_ptr<Entity> ghost(new Ghost(colors[i]));

        em.list.push_back(ghost);
    }

    shared_ptr<Entity> player(new Player);
    em.list.push_back(player);
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime.
    static Clock clock;
    float dt = clock.restart().asSeconds();

    for (auto& e : em.list) {
        e->Update(dt);
    }
}

void Render(RenderWindow& window) {
    for (auto& e : em.list) {
        e->Render(window);
    }

    Renderer::render();
}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "Pacman");
    Renderer::initialise(window);
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