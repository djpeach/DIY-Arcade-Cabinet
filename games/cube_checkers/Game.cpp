#include "Game.hpp"

Game::Game(std::string name) :
window(sf::VideoMode::getDesktopMode(), name, sf::Style::Fullscreen) {}

void Game::run() {
  while (window.isOpen()) {
    sf::Event e;

    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color(220, 220, 220));
    window.display();
  }
}
