#pragma once

#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
public:
  Tile(sf::Vector2f size, sf::Vector2f pos, sf::Color color);

  void setColor(sf::Color color);

  void draw(sf::RenderTarget & target, sf::RenderStates states) const;
private:
  sf::RectangleShape rect;
  bool selected;
};