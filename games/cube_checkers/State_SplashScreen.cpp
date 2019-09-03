#include "State_SplashScreen.hpp"

State_SplashScreen::State_SplashScreen(sf::RenderWindow & window, std::string name) : State_Base(window, name) {}

State_SplashScreen::~State_SplashScreen() {}

void State_SplashScreen::update() {
  std::cout << name << ": update from state_splashScreen" << std::endl;
}

void State_SplashScreen::render() {
  std::cout << name << ": render from state_splashScreen" << std::endl;
}
