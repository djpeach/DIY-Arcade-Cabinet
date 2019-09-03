#include <iostream>

#include "State_Instructions.hpp"
#include "Game.hpp"

State_Instructions::State_Instructions(SharedContext & ctx) : State_Base(ctx),
bodyText() {
  if (!font.loadFromFile("assets/font/Regular.ttf")) {
    std::cerr << "State_Instructions could not load font from file: assets/font/Regular.ttf" << std::endl;
    exit(1);
  }

  bodyText.setFont(font);
  bodyText.setFillColor(sf::Color::Black);
  bodyText.setCharacterSize(140);
  bodyText.setString("Instructions");
  sf::FloatRect bodyTextBounds = bodyText.getGlobalBounds();
  // bodyText.setOrigin(bodyTextBounds.width / 2, bodyTextBounds.height / 2);
}

State_Instructions::~State_Instructions() {}

void State_Instructions::handleEvent(sf::Event e) {
  if (e.type == sf::Event::Closed) {
    ctx.window.close();
  }
}

void State_Instructions::update() {}

void State_Instructions::render() {
  ctx.window.clear(sf::Color::Red);
  ctx.window.draw(bodyText);
}
