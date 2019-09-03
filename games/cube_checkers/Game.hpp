#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Game {
public:
  Game(std::string name);

  void run();
private:
  sf::RenderWindow window;
};
