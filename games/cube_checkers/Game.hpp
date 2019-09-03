#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "StateMachine.hpp"

struct SharedContext {
  SharedContext(std::string name) :
  window(sf::VideoMode::getDesktopMode(), name, sf::Style::Fullscreen),
  stateMachine() {}

  sf::RenderWindow window;
  StateMachine stateMachine;
};

class Game {
public:
  Game(std::string name);

  void run();
private:
  SharedContext ctx;
};
