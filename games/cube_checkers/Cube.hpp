#pragma once

#include <SFML/Graphics.hpp>

class Cube {
public:
  Cube(sf::Vector2f size, sf::Vector2f pos, sf::Color color);

  sf::Vector2f getSize();
  sf::FloatRect getBounds();

  void highlight();
  void unhighlight();

  void draw(sf::RenderWindow & window);
private:
  sf::RectangleShape rect;
  int value;
public:
  sf::Text valueText;
  sf::Font font;
};
