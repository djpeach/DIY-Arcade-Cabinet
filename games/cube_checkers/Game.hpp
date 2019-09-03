#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "StateMachine.hpp"

class Game {
public:
  Game(std::string name);

  void run();
private:
  sf::RenderWindow window;
  StateMachine stateMachine;
};
