#include <string>
#include <iostream>

#include "Cube.hpp"

int counter = 0;

Cube::Cube(sf::Vector2f size, sf::Vector2f pos, sf::Color color) :
value(1), font(), rect(), valueText("", font, 60) {
  rect.setSize(size);
  rect.setOrigin(size.x / 2, size.y / 2);
  rect.setPosition(pos);
  rect.setFillColor(color);
  std::string valueString = std::to_string(value);
  valueText.setString(valueString);
  sf::FloatRect valueTextBounds = valueText.getGlobalBounds();
  valueText.setOrigin(valueTextBounds.width / 2, valueTextBounds.height / 2);
  valueText.setPosition(rect.getPosition().x - 12, rect.getPosition().y - 30);
}

sf::Vector2f Cube::getSize() {
  return rect.getSize();
}

sf::FloatRect Cube::getBounds() {
  return rect.getGlobalBounds();
}

sf::Vector2f Cube::getPosition() {
  return rect.getPosition();
}

void Cube::setPosition(sf::Vector2f pos) {
  valueText.setPosition(pos.x - 12, pos.y - 30);
  rect.setPosition(pos);
}

void Cube::highlight() {
  rect.setOutlineThickness(5);
}

void Cube::unhighlight() {
  rect.setOutlineThickness(0);
}

void Cube::draw(sf::RenderWindow & window) {
  window.draw(rect);

  if (!font.loadFromFile("assets/font/Regular.ttf")) {
    std::cerr << "Cube could not load font from file: assets/font/Regular.ttf" << std::endl;
    exit(1);
  }
  valueText.setFont(font);

  window.draw(valueText);
}
