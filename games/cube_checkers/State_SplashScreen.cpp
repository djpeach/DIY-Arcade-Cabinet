#include "State_SplashScreen.hpp"
#include "State_MainMenu.hpp"
#include "Game.hpp"

State_SplashScreen::State_SplashScreen(SharedContext & ctx) : State_Base(ctx) {
  if (!font.loadFromFile("assets/font/Regular.ttf")) {
    std::cerr << "State_SplashScreen could not load font from file: assets/font/Regular.ttf" << std::endl;
    exit(1);
  }

  titleText.setFont(font);
  titleText.setFillColor(sf::Color::Red);
  titleText.setCharacterSize(140);
  titleText.setString("Cube Checkers");
  sf::FloatRect titleTextBounds = titleText.getLocalBounds();
  titleText.setOrigin(titleTextBounds.width / 2, titleTextBounds.height / 2);

  introText.setFont(font);
  introText.setCharacterSize(80);
  introText.setString("Press any button to start...");
  sf::FloatRect introTextBounds = introText.getLocalBounds();
  introText.setOrigin(introTextBounds.width / 2, introTextBounds.height / 2);

  sf::Vector2u windowSize = ctx.window.getSize();
  titleText.setPosition(windowSize.x / 2, windowSize.y / 2 - 100);
  introText.setPosition(windowSize.x / 2, windowSize.y / 2 + 100);
}

State_SplashScreen::~State_SplashScreen() {}

void State_SplashScreen::handleEvent(sf::Event e) {
  if (e.type == sf::Event::Closed) {
    ctx.window.close();
  } else if (e.type == sf::Event::KeyPressed) {
    ctx.stateMachine.pushState(std::make_unique<State_MainMenu>(ctx));
  }
}

void State_SplashScreen::update() {}

void State_SplashScreen::render() {
  ctx.window.draw(titleText);
  ctx.window.draw(introText);
}
