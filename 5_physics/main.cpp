#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace std;
using namespace sf;

int gameWidth = 1000;
int gameHeight = 1000;

b2World* world;

vector<b2Body*> bodies;
vector<RectangleShape*> sprites;

const float physics_scale = 30.0f;
const float physics_scale_inv = 1.0f / physics_scale;

const int32 velocityIterations = 6;
const int32 positionIterations = 2;

//Convert from b2Vec2 to a Vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in) {
    return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}
//Convert from Vector2f to a b2Vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
    return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}
//Convert from screenspace.y to physics.y (as they are the other way around)
inline const Vector2f invert_height(const Vector2f& in) {
    return Vector2f(in.x, gameHeight - in.y);
}

// Create a box2d bosy with box fixture
b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const Vector2f& position, const Vector2f& size) {
    b2BodyDef BodyDef;

    BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
    BodyDef.position = sv2_to_bv2(position);

    b2Body* body = World.CreateBody(&BodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
    b2FixtureDef fixtureDef;

    fixtureDef.density = dynamic ? 10.f : 0.0f;
    fixtureDef.friction = dynamic ? 0.8f : 1.f;
    fixtureDef.restitution = 0.5;
    fixtureDef.shape = &shape;

    body->CreateFixture(&fixtureDef);
    return body;
}

// Create a Box2d body with a box fixture, from a sfml::RectangleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs) {
    return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void init() {
	const b2Vec2 gravity(0.0f, -30.0f);

	world = new b2World(gravity);

    // Create boxes
    for (int i = 0; i < 11; i++)
    {
        auto s = new RectangleShape();
        s->setPosition(Vector2f(i * (gameWidth / 12.f), gameHeight * .7f));
        s->setSize(Vector2f(50.f, 50.f));
        s->setOrigin(Vector2f(25.f, 25.f));
        s->setFillColor(Color::White);

        sprites.push_back(s);

        auto b = CreatePhysicsBox(*world, true, *s);
        b->ApplyAngularImpulse(5.0f, true);
        bodies.push_back(b);
    }

    // Walls
    Vector2f walls[] = {
        // Top
        Vector2f(gameWidth * .5f, 5.f), Vector2f(gameWidth, 10.f),
        // Bot
        Vector2f(gameWidth * .5f, gameHeight - 5.f), Vector2f(gameWidth, 10.f),
        // Left
        Vector2f(5.f, gameHeight * .5f), Vector2f(10.f, gameHeight),
        // Right
        Vector2f(gameWidth - 5.f, gameHeight * .5f), Vector2f(10.f, gameHeight)
    };

    // Build walls
    for (int i = 0; i < 7; i+=2)
    {
        auto x = new RectangleShape();
        x->setPosition(walls[i]);
        x->setSize(walls[i + 1]);
        x->setOrigin(walls[i + 1] * .5f);
        x->setFillColor(Color::Red);

        sprites.push_back(x);

        auto b = CreatePhysicsBox(*world, false, *x);
        bodies.push_back(b);
    }
}

void Update(RenderWindow& window) {
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();

    // Check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    world->Step(dt, velocityIterations, positionIterations);

    for (int i = 0; i < bodies.size(); i++) {
        sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
        sprites[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
    }
}

void Render(RenderWindow& window) {
    for each (auto var in sprites)
    {
        window.draw(*var);
    }
}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "Physics");
    init();

    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }

    return 0;
}