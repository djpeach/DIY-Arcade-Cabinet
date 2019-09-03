#pragma once

#include <SFML/Graphics.hpp>

struct SharedContext;

class State_Base {
public:
  State_Base(SharedContext & ctx);
  virtual ~State_Base();

  virtual void handleEvent(sf::Event e) = 0;
  virtual void update() = 0;
  virtual void render() = 0;
protected:
  SharedContext & ctx;
};
