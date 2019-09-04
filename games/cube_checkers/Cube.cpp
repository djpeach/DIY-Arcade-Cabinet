#include <string>
#include <iostream>

#include "Cube.hpp"

int counter = 0;

Cube::Cube(sf::Vector2f size, sf::Vector2f pos, sf::Color color) :
value(1), font(), rect(), valueText("", font, 40) {
  rect.setSize(size);
  rect.setOrigin(size.x / 2, size.y / 2);
  rect.setPosition(pos);
  rect.setFillColor(color);

  if (!font.loadFromFile("assets/font/Regular.ttf")) {
    std::cerr << "Cube could not load font from file: assets/font/Regular.ttf" << std::endl;
    exit(1);
  }
  // std::string valueString = std::to_string(value);
  valueText.setString("1");
  // sf::FloatRect valueTextBounds = valueText.getGlobalBounds();
  // valueText.setOrigin(valueTextBounds.width / 2, valueTextBounds.height / 2);
  valueText.setPosition(rect.getPosition());
}

sf::Vector2f Cube::getSize() {
  return rect.getSize();
}

void Cube::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(rect, states);
  target.draw(valueText, states);
}
