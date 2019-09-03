#pragma once

#include <SFML/Graphics.hpp>

#include "State_Base.hpp"

struct SharedContext;

class State_Game : public State_Base {
public:
  State_Game(SharedContext & ctx);
  ~State_Game();

  void handleEvent(sf::Event e);
  void update();
  void render();
private:
  sf::Text bodyText;
  sf::Font font;
};
