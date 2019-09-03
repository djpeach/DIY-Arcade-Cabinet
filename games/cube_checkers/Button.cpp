#include <iostream>

#include "Button.hpp"

#define PADDING 50

Button::Button() :
isSelected(false),
rect(),
font(),
text("", font, 50) {
  if (!font.loadFromFile("assets/font/Regular.ttf")) {
    std::cerr << "State_SplashScreen could not load font from file: assets/font/Regular.ttf" << std::endl;
    exit(1);
  }

  adjustRectSize();
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(rect, states);
  target.draw(text, states);
}

void Button::setBackgroundColor(const sf::Color & color) {
  rect.setFillColor(color);
}

void Button::setOrigin(const sf::Vector2f & origin) {
  rect.setOrigin(origin.x, origin.y);
}

void Button::setPosition(const sf::Vector2f & position) {
  rect.setPosition(position);
  adjustRectSize();
}

const sf::Vector2f & Button::getSize() {
  return rect.getSize();
}

void Button::setFontColor(const sf::Color & color) {
  text.setFillColor(color);
}

void Button::setLabel(const std::string & label) {
  text.setString(label);
  adjustRectSize();
}

void Button::setFontSize(unsigned int size) {
  text.setCharacterSize(size);
  adjustRectSize();
}

void Button::adjustRectSize() {
  sf::FloatRect textBounds = text.getGlobalBounds();
  rect.setSize(sf::Vector2f(textBounds.width + PADDING, textBounds.height + PADDING));
  sf::FloatRect rectBounds = rect.getGlobalBounds();
  text.setPosition(sf::Vector2f(rectBounds.left + PADDING * 0.5, rectBounds.top + PADDING * 0.4));
}

void Button::setSelected(bool isSelected) {
  this->isSelected = isSelected;
  rect.setOutlineThickness(this->isSelected * 5);
}

bool Button::getSelected() { return isSelected; }

void Button::toggleSelected() {
  isSelected = !isSelected;
  rect.setOutlineThickness(isSelected * 5);
}
