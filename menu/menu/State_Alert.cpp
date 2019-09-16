#include "State_Alert.hpp"
#include "SharedContext.hpp"

#include <string>
#include "stdlib.h"

State_Alert::State_Alert(SharedContext * ctx) : State_Base(ctx) {
    setTransparent(true);
}
State_Alert::~State_Alert() {}

void State_Alert::onCreate() {
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    alertBox.setSize(sf::Vector2f(windowSize.x * .8 , windowSize.y * .8 ));
    alertBox.setFillColor(sf::Color(50, 50, 50));
    alertBox.setOutlineColor(sf::Color(240, 20, 20));
    alertBox.setOutlineThickness(10);
    sf::Vector2f alertBoxSize = alertBox.getSize();
    alertBox.setOrigin(alertBoxSize.x / 2, alertBoxSize.y / 2);
    alertBox.setPosition(windowSize.x / 2, windowSize.y / 2);

    ctx->eventManager->addCallback(StateType::Alert, "player1Go", &State_Alert::backToMenu, this);
    ctx->eventManager->addCallback(StateType::Alert, "player2Go", &State_Alert::backToMenu, this);
    ctx->eventManager->addCallback(StateType::Alert, "slashClose", &State_Alert::backToMenu, this);
}

void State_Alert::onDestroy() {
    ctx->eventManager->removeCallback(StateType::Alert, "player1Go");
    ctx->eventManager->removeCallback(StateType::Alert, "player2Go");
    ctx->eventManager->removeCallback(StateType::Alert, "slashClose");
}

void State_Alert::activate() {
}

void State_Alert::deactivate() {}

void State_Alert::update(const sf::Time & delta) {}

void State_Alert::draw() {
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    sf::RectangleShape rect(sf::Vector2f(windowSize.x, windowSize.y));
    rect.setFillColor(sf::Color(0, 0, 0, 200));
    ctx->window->getRenderWindow()->draw(rect);
    ctx->window->getRenderWindow()->draw(alertBox);
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Could not load font from assets/fonts/arial.ttf" << std::endl;
        exit(1);
    }

    sf::Text text;
    text.setString("This game does not support " + this->mode);
    text.setFont(font);
    text.setCharacterSize(35);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(alertBox.getPosition().x, alertBox.getPosition().y - 50);
    ctx->window->getRenderWindow()->draw(text);

    text.setString("Press the Control Button to go back to the menu");
    text.setFont(font);
    text.setCharacterSize(35);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(alertBox.getPosition().x, alertBox.getPosition().y + 50);
    ctx->window->getRenderWindow()->draw(text);
}

void State_Alert::setGameMode(std::string mode) {
    this->mode = mode;
}

void State_Alert::backToMenu(BindingDetails * details) {
    ctx->stateMachine->changeState(StateType::DIYACMenu);
}
