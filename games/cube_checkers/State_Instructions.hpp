#pragma once

#include <SFML/Graphics.hpp>

#include "State_Base.hpp"

struct SharedContext;

class State_Instructions : public State_Base {
public:
  State_Instructions(SharedContext & ctx);
  ~State_Instructions();

  void handleEvent(sf::Event e);
  void update();
  void render();
private:
  sf::Text bodyText;
  sf::Font font;
};
