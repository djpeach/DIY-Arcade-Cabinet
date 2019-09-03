#pragma once

#include <vector>
#include <memory>

#include "State_Base.hpp"

class StateMachine {
public:
  StateMachine();

  void addState(std::unique_ptr<State_Base> state);
  void run();
private:
  std::vector<std::unique_ptr<State_Base>> states;
};
