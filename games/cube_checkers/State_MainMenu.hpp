#pragma once

#include <SFML/Graphics.hpp>

#include "State_Base.hpp"
#include "Button.hpp"

struct SharedContext;

class State_MainMenu : public State_Base {
public:
  State_MainMenu(SharedContext & ctx);
  ~State_MainMenu();

  void handleEvent(sf::Event e);
  void update();
  void render();
private:
  sf::Text titleText;
  sf::Text instructionText;
  sf::Font font;
  Button playBtn;
  Button instructionsBtn;
};
