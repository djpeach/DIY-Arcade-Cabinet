#include "StateMachine.hpp"

StateMachine::StateMachine() {}

void StateMachine::run() {
  for (auto & state : states) {
    state->update();
    state->render();
  }
}
