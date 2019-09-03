#include "StateMachine.hpp"

StateMachine::StateMachine() {}

void StateMachine::addState(std::unique_ptr<State_Base> state) {
  states.push_back(std::move(state));
}

void StateMachine::run() {
  for (auto & state : states) {
    state->update();
    state->render();
  }
}
