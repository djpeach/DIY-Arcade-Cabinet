#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
  Button();

  void draw(sf::RenderTarget & target, sf::RenderStates states) const;

  void setBackgroundColor(const sf::Color & color);
  void setOrigin(const sf::Vector2f & origin);
  void setPosition(const sf::Vector2f & position);
  const sf::Vector2f & getSize();

  void setFontColor(const sf::Color & color);
  void setLabel(const std::string & label);
  void setFontSize(unsigned int size);

  void setSelected(bool isSelected);
  bool getSelected();
  void toggleSelected();
private:
  void adjustRectSize();

  sf::RectangleShape rect;
  sf::Text text;
  sf::Font font;

  bool isSelected;
};
