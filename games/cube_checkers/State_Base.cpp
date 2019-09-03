#include "State_Base.hpp"

State_Base::State_Base(sf::RenderWindow & window, std::string name) :
window(window),
name(name) {}

State_Base::~State_Base() {}

