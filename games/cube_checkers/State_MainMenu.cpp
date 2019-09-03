#include <iostream>

#include "State_MainMenu.hpp"
#include "State_SplashScreen.hpp"
#include "State_Instructions.hpp"
#include "State_Game.hpp"
#include "Game.hpp"

State_MainMenu::State_MainMenu(SharedContext & ctx) : State_Base(ctx),
titleText(), instructionText(),
playBtn(), instructionsBtn() {
  if (!font.loadFromFile("assets/font/Regular.ttf")) {
    std::cerr << "State_MainMenu could not load font from file: assets/font/Regular.ttf" << std::endl;
    exit(1);
  }

  titleText.setFont(font);
  titleText.setFillColor(sf::Color::Red);
  titleText.setCharacterSize(140);
  titleText.setString("Main Menu");
  sf::FloatRect titleTextBounds = titleText.getGlobalBounds();
  titleText.setOrigin(titleTextBounds.width / 2, titleTextBounds.height / 2);

  instructionText.setFont(font);
  instructionText.setCharacterSize(50);
  instructionText.setString("Press Red to select");
  sf::FloatRect instructionTextBounds = instructionText.getGlobalBounds();
  instructionText.setOrigin(instructionTextBounds.width / 2, instructionTextBounds.height / 2);

  sf::Vector2u windowSize = ctx.window.getSize();
  titleText.setPosition(windowSize.x / 2, windowSize.y / 2 - 500);
  instructionText.setPosition(windowSize.x / 2, windowSize.y / 2 - 370);

  playBtn.setBackgroundColor(sf::Color::Red);
  playBtn.setLabel("Play Cube Checkers");
  playBtn.setOrigin(sf::Vector2f(playBtn.getSize().x / 2, playBtn.getSize().y / 2));
  playBtn.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 - 150));
  playBtn.setSelected(true);

  instructionsBtn.setBackgroundColor(sf::Color::Red);
  instructionsBtn.setLabel("How to Play");
  instructionsBtn.setOrigin(sf::Vector2f(instructionsBtn.getSize().x / 2, instructionsBtn.getSize().y / 2));
  instructionsBtn.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::handleEvent(sf::Event e) {
  if (e.type == sf::Event::Closed) {
    ctx.window.close();
  } else if (e.type == sf::Event::KeyPressed) {
    switch(e.key.code) {
      case sf::Keyboard::W:
      case sf::Keyboard::S:
      case sf::Keyboard::I:
      case sf::Keyboard::K:
        playBtn.toggleSelected();
        instructionsBtn.toggleSelected();
        break;
      case sf::Keyboard::F:
      case sf::Keyboard::H:
        if (playBtn.getSelected()) {
          ctx.stateMachine.pushState(std::make_unique<State_Game>(ctx), false);
        } else if (instructionsBtn.getSelected()) {
          ctx.stateMachine.pushState(std::make_unique<State_Instructions>(ctx), false);
        }
      default:
        break;
    }
  }
}

void State_MainMenu::update() {}

void State_MainMenu::render() {
  ctx.window.draw(titleText);
  ctx.window.draw(instructionText);
  ctx.window.draw(playBtn);
  ctx.window.draw(instructionsBtn);
}
