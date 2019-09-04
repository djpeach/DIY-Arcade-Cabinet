#include <string>
#include <iostream>

#include "Cube.hpp"

Cube::Cube() :
value(1) {
  if (!font.loadFromFile("assets/font/Bold.ttf")) {
    std::cerr << "Cube could not load font from file: assets/font/Bold.ttf" << std::endl;
    exit(1);
  }

  std::string valueString = std::to_string(value);
  valueText.setString(valueString);
}

void Cube::setColor(sf::Color color) {
  rect.setFillColor(color);
}

void Cube::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(rect, states);
  target.draw(valueText, states);
}
