#pragma once

#include <SFML/Graphics.hpp>

class Cube {
public:
  int value;
  int index;

  Cube(sf::Vector2f size, sf::Vector2f pos, sf::Color color);

  sf::Vector2f getSize();
  sf::FloatRect getBounds();
  sf::Vector2f getPosition();

  void setPosition(sf::Vector2f pos);

  void highlight();
  void unhighlight();

  void draw(sf::RenderWindow & window);
private:
  sf::RectangleShape rect;
  sf::Text valueText;
  sf::Font font;
};
