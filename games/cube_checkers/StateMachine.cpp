#include "StateMachine.hpp"

StateMachine::StateMachine() {}

void StateMachine::addState(std::unique_ptr<State_Base> state) {
  states.push_back(std::move(state));
}

void StateMachine::handleEvent(sf::Event e) {
  auto & topState = states.back();
  topState->handleEvent(e);
}

void StateMachine::updateStates() {
  for (auto & state : states) {
    state->update();
  }
}

void StateMachine::renderStates() {
  for (auto & state : states) {
    state->render();
  }
}
