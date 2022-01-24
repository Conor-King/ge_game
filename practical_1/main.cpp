#include <SFML/Graphics.hpp>

int main(){
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape circleShape(90.f);
  circleShape.setFillColor(sf::Color::Magenta);
  circleShape.setPosition(sf::Vector2f(10, 10));

  sf::RectangleShape rectShape;
  rectShape.setSize(sf::Vector2f(200,200));
  rectShape.setFillColor(sf::Color::Cyan);

  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    window.draw(rectShape);
    window.draw(circleShape);
    window.display();
  }
  return 0;
}