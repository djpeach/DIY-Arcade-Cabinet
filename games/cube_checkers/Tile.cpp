#include "Tile.hpp"

Tile::Tile(sf::Vector2f size, sf::Vector2f pos, sf::Color color) :
selected(false) {
  rect.setPosition(pos);
  rect.setSize(size);
  rect.setFillColor(color);
}

void Tile::setColor(sf::Color color) {
  rect.setFillColor(color);
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(rect, states);
}
