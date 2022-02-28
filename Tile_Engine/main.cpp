#include "Entity.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

unique_ptr<Player> player(new Player);

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
    player->Render(window);
}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}