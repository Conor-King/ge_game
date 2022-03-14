#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

unique_ptr<Player> _player(new Player);

void Load() {
    
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime.
    static Clock clock;
    float dt = clock.restart().asSeconds();

    _player->Update(dt);

}

void Render(RenderWindow& window) {
   
    _player->Render(window);
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