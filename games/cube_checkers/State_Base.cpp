#include "State_Base.hpp"

State_Base::State_Base(sf::RenderWindow & window, std::string name) :
window(window),
name(name) {}

void State_Base::update() {
  std::cout << name << ": update from state_base" << std::endl;
}

void State_Base::render() {
  std::cout << name << ": render from state_base" << std::endl;
}

