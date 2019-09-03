#include "Game.hpp"
#include "State_Base.hpp"
#include "State_SplashScreen.hpp"

Game::Game(std::string name) :
window(sf::VideoMode::getDesktopMode(), name, sf::Style::Fullscreen),
stateMachine() {}

void Game::run() {

  auto introState = std::make_unique<State_SplashScreen>(window, "Intro State");
  stateMachine.addState(std::move(introState));

  stateMachine.run();
  // while (window.isOpen()) {
  //   sf::Event e;

  //   while (window.pollEvent(e)) {
  //     if (e.type == sf::Event::Closed) {
  //       window.close();
  //     }
  //   }

  //   window.clear(sf::Color(220, 220, 220));
  //   window.display();
  // }
}
