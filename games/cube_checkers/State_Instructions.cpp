#include <iostream>

#include "State_Instructions.hpp"
#include "Game.hpp"

#define PADDING 50

State_Instructions::State_Instructions(SharedContext & ctx) : State_Base(ctx),
bodyText(), getBackText() {

  if (!font.loadFromFile("assets/font/Bold.ttf")) {
    std::cerr << "State_Instructions could not load font from file: assets/font/Bold.ttf" << std::endl;
    exit(1);
  }

  getBackText.setFont(font);
  getBackText.setCharacterSize(45);
  getBackText.setString("Press Red to go back");
  getBackText.setPosition(PADDING, PADDING);

  bodyText.setFont(font);
  bodyText.setFillColor(sf::Color::Black);
  bodyText.setCharacterSize(30);
  std::string bodyTextString =
  "\nCube Checkers plays like regualar checkers. You must play all your pieces on the dark squares. \n"
  "Pieces can only move diagnolly forward, and you must jump an opponent's piece if you can. A \n"
  "piece that makes it to the other side becomes a king and can move diagnolly both directions. \n\n"
  "However, with Cube Checkers, each piece has a value. 1 being the beginning value and 6 being \n"
  "a king. You can only jump pieces that are lower or equal to rank to you. Pieces gain rank by \n"
  "being 'flipped'. You flip a piece at the end of every turn. But you may not flip the piece that \n"
  "you moved, and you flip no pieces after a jump. The game is over when all your opponents pieces \n"
  "are gone, or cannot make another move.";
  bodyText.setString(bodyTextString);
  bodyText.setPosition(PADDING, (PADDING + getBackText.getCharacterSize() + 30));
}

State_Instructions::~State_Instructions() {}

void State_Instructions::handleEvent(sf::Event e) {
  if (e.type == sf::Event::Closed) {
    ctx.window.close();
  } else if (e.type == sf::Event::KeyPressed) {
    switch (e.key.code) {
      case sf::Keyboard::F:
      case sf::Keyboard::H:
        ctx.stateMachine.popState();
        break;
      case sf::Keyboard::Slash:
        ctx.window.close();
        break;
      default:
        break;
    }
  }
}

void State_Instructions::update() {}

void State_Instructions::render() {
  ctx.window.clear(sf::Color(200, 15, 15));
  ctx.window.draw(getBackText);
  ctx.window.draw(bodyText);
}
