#include "StateMachine.hpp"

StateMachine::StateMachine() {}

void StateMachine::pushState(std::unique_ptr<State_Base> state, bool shouldPopCurrent) {
  if (!states.empty() && shouldPopCurrent) {
    states.pop();
  }
  states.push(std::move(state));
}

void StateMachine::popState() {
  if (!states.empty()) {
    states.pop();
  }
}

void StateMachine::handleEvent(sf::Event e) {
  states.top()->handleEvent(e);
}

void StateMachine::updateStates() {
  states.top()->update();
}

void StateMachine::renderStates() {
  states.top()->render();
}
