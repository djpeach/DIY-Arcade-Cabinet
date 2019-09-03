#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "State_Base.hpp"

class StateMachine {
public:
  StateMachine();

  void addState(std::unique_ptr<State_Base> state);

  void handleEvent(sf::Event e);
  void updateStates();
  void renderStates();
private:
  std::vector<std::unique_ptr<State_Base>> states;
};
