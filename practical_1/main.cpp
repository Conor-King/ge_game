#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A,
    Keyboard::Z,
    Keyboard::Up,
    Keyboard::Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

void Load() {

    // Set size and origin of paddles
    for (auto &p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }

    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(Vector2f(10, 10));

    // Reset paddle position
    paddles[0].setPosition(Vector2(10.f + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2(gameWidth - 10.f - paddleSize.x / 2.f, gameHeight / 2.f));

    // Reset ball position
    ball.setPosition(Vector2(gameWidth / 2.f - 10.f, gameHeight / 2.f - 10.f));
}

void Update(RenderWindow &window) {
    
    // Reset clock, recalculate deltatime.
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

    // handle paddle movement
    float direction = 0.f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(Vector2(0.f, direction * paddleSpeed * dt));
}

void Render(RenderWindow &window) {
    // Draw everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main(){
  
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}