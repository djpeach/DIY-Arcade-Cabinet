#pragma once

#include <stack>
#include <memory>

#include <SFML/Graphics.hpp>

#include "State_Base.hpp"

class StateMachine {
public:
  StateMachine();

  void pushState(std::unique_ptr<State_Base> state, bool shouldPopCurrent = true);
  void popState();

  void handleEvent(sf::Event e);
  void updateStates();
  void renderStates();
private:
  std::stack<std::unique_ptr<State_Base>> states;
};
