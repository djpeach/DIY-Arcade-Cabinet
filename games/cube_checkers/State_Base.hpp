#include <iostream>

#include <SFML/Graphics.hpp>

class State_Base {
public:
  State_Base(sf::RenderWindow & window);

  void update();
  void render();
private:
  bool isTransparent;
  sf::RenderWindow & window;
};
