#include "Game.hpp"
#include "State_Base.hpp"
#include "State_SplashScreen.hpp"

Game::Game(std::string name) :
ctx(name) {
  ctx.stateMachine.pushState(std::make_unique<State_SplashScreen>(ctx));
}

void Game::run() {
  while(ctx.window.isOpen()) {
    sf::Event e;
    while(ctx.window.pollEvent(e)) {
      ctx.stateMachine.handleEvent(e);
    }

    ctx.stateMachine.updateStates();

    ctx.window.clear();
    ctx.stateMachine.renderStates();
    ctx.window.display();
  }
}
