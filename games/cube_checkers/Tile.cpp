#include "Tile.hpp"

Tile::Tile() {}

Tile::Tile(sf::Vector2f size, sf::Vector2f pos, sf::Color color) :
selected(false) {
  rect.setPosition(pos);
  rect.setSize(size);
  rect.setFillColor(color);
}

void Tile::setPosition(sf::Vector2f pos) {
  rect.setPosition(pos);
}

sf::Vector2f Tile::getPosition() {
  sf::RectangleShape rectToReturn = rect;
  return sf::Vector2f(rectToReturn.getPosition().x + rect.getSize().x / 2, rectToReturn.getPosition().y + rect.getSize().y / 2);
}

void Tile::setColor(sf::Color color) {
  rect.setFillColor(color);
}

sf::FloatRect Tile::getBounds() {
  return rect.getGlobalBounds();
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(rect, states);
}
