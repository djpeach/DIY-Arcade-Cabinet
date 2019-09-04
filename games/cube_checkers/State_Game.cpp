#include <iostream>

#include "State_Game.hpp"
#include "Game.hpp"

State_Game::State_Game(SharedContext & ctx) : State_Base(ctx),
bodyText() {
  if (!font.loadFromFile("assets/font/Regular.ttf")) {
    std::cerr << "State_Game could not load font from file: assets/font/Regular.ttf" << std::endl;
    exit(1);
  }

  bodyText.setFont(font);
  bodyText.setFillColor(sf::Color::Black);
  bodyText.setCharacterSize(140);
  bodyText.setString("Game");
  sf::FloatRect bodyTextBounds = bodyText.getGlobalBounds();
  // bodyText.setOrigin(bodyTextBounds.width / 2, bodyTextBounds.height / 2);
}

State_Game::~State_Game() {}

void State_Game::handleEvent(sf::Event e) {
  if (e.type == sf::Event::Closed) {
    ctx.window.close();
  }
}

void State_Game::update() {}

void State_Game::render() {
  ctx.window.clear(sf::Color::Blue);
  ctx.window.draw(bodyText);
}
