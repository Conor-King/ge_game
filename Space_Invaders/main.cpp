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

Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

void Reset() {
    // Reset paddle position
    paddles[0].setPosition(Vector2(10.f + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2(gameWidth - 10.f - paddleSize.x / 2.f, gameHeight / 2.f));

    // Reset ball position
    ball.setPosition(Vector2(gameWidth / 2.f - 10.f, gameHeight / 2.f - 10.f));

    ballVelocity = { (server ? 100.f : -100.f), 60.f };
}

void Load() {

    // Set size and origin of paddles
    for (auto &p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }

    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(Vector2f(10, 10));

    Reset();
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

    float direction2 = 0.f;
    if (Keyboard::isKeyPressed(controls[2])) {
        direction2--;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        direction2++;
    }
    paddles[1].move(Vector2(0.f, direction2 * paddleSpeed * dt));

    // Handle ball movement
    ball.move(ballVelocity * dt);

    // Ball edge bounce
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { // Bottom Wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(Vector2(0.f, -10.f));
    }
    else if (by < 0) { // Top Wall
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(Vector2(0.f, 10.f));
    }
    else if (bx > gameWidth) { // Right Wall
        Reset();
    }
    else if (bx < 0) { // Left Wall
        Reset();
    }
    else if (
        // ball is inline or behind the paddle
        bx < paddles[0].getPosition().x + (paddleSize.x * 0.5) &&
        // AND ball is below top edge
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        // AND ball is above the bottom edge
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
        ) {
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(Vector2(10.f, 0.f));
    }
    else if (
        // ball is inline or behind the paddle
        bx > paddles[1].getPosition().x - (paddleSize.x * 0.5) &&
        // AND ball is below top edge
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
        // AND ball is above the bottom edge
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
        ) {
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(Vector2(-10.f, 0.f));
    }

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