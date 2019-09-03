#include <vector>
#include <memory>

#include "State_Base.hpp"

class StateMachine {
public:
  StateMachine();

  void addState(); // TODO: Determine what to pass in to add to states as a unique_ptr

  void run();
private:
  std::vector<std::unique_ptr<State_Base>> states;
};
