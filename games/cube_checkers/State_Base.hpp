#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

class State_Base {
public:
  State_Base(sf::RenderWindow & window, std::string name);
  virtual ~State_Base();

  virtual void update() = 0;
  virtual void render() = 0;
protected:
  bool isTransparent;
  sf::RenderWindow & window;
  std::string name;
};
