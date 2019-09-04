#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
public:
  int index;

  Tile();
  Tile(sf::Vector2f size, sf::Vector2f pos, sf::Color color);

  void setColor(sf::Color color);
  void setPosition(sf::Vector2f pos);
  sf::FloatRect getBounds();
  sf::Vector2f getPosition();

  void draw(sf::RenderTarget & target, sf::RenderStates states) const;
private:
  sf::RectangleShape rect;
  bool selected;
};
