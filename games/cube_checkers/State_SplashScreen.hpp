#pragma once

#include "State_Base.hpp"

class State_SplashScreen : public State_Base {
public:
  State_SplashScreen(sf::RenderWindow & window, std::string name);
  ~State_SplashScreen();

  void update();
  void render();
};
