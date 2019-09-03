#include "State_Base.hpp"

State_Base::State_Base(sf::RenderWindow & window) :
window(window) {}

void State_Base::update() {
  std::cout << "update from state_base" << std::endl;
}

void State_Base::render() {
  std::cout << "render from state_base" << std::endl;
}

