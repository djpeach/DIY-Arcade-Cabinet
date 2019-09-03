#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

class State_Base {
public:
  State_Base(sf::RenderWindow & window, std::string name);

  void update();
  void render();
private:
  bool isTransparent;
  sf::RenderWindow & window;
  std::string name;
};
