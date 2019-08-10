#include "State_Instructions.hpp"
#include "SharedContext.hpp"

#include <string>
#include "stdlib.h"

State_Instructions::State_Instructions(SharedContext * ctx) : State_Base(ctx) {
    setTransparent(true);
}
State_Instructions::~State_Instructions() {}

void State_Instructions::onCreate() {}

void State_Instructions::onDestroy() {}

void State_Instructions::activate() {
    std::cout << "drawing instructions" << std::endl;
}

void State_Instructions::deactivate() {}

void State_Instructions::update(const sf::Time & delta) {}
void State_Instructions::draw() {
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    sf::RectangleShape rect(sf::Vector2f(windowSize.x, windowSize.y));
    rect.setFillColor(sf::Color(0, 0, 0, 200));
    ctx->window->getRenderWindow()->draw(rect);
}
