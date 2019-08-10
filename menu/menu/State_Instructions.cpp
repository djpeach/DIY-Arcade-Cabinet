#include "State_Instructions.hpp"
#include "SharedContext.hpp"

#include <string>
#include "stdlib.h"

State_Instructions::State_Instructions(SharedContext * ctx) : State_Base(ctx) {
    setTransparent(true);
}
State_Instructions::~State_Instructions() {}

void State_Instructions::onCreate() {
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    introBox.setSize(sf::Vector2f(windowSize.x * .8 , windowSize.y * .8 ));
    introBox.setFillColor(sf::Color(50, 50, 50));
    introBox.setOutlineColor(sf::Color(240, 20, 20));
    introBox.setOutlineThickness(10);
    sf::Vector2f introBoxSize = introBox.getSize();
    introBox.setOrigin(introBoxSize.x / 2, introBoxSize.y / 2);
    introBox.setPosition(windowSize.x / 2, windowSize.y / 2);
    
    ctx->eventManager->addCallback(StateType::Instructions, "gameStart1Player", &State_Instructions::startGame, this);
    ctx->eventManager->addCallback(StateType::Instructions, "gameStart2Player", &State_Instructions::startGame, this);
    ctx->eventManager->addCallback(StateType::Instructions, "backToMenu", &State_Instructions::backToMenu, this);
}

void State_Instructions::onDestroy() {}

void State_Instructions::activate() {
}

void State_Instructions::deactivate() {}

void State_Instructions::update(const sf::Time & delta) {}

void State_Instructions::draw() {
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    sf::RectangleShape rect(sf::Vector2f(windowSize.x, windowSize.y));
    rect.setFillColor(sf::Color(0, 0, 0, 200));
    ctx->window->getRenderWindow()->draw(rect);
    ctx->window->getRenderWindow()->draw(introBox);
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Could not load font from assets/fonts/arial.ttf" << std::endl;
        exit(1);
    }
    game.name.setFont(font);
    float textHeight = game.name.getGlobalBounds().height;
    float rowHeight = 30;
    int curRow = 1;
    game.name.setCharacterSize(60);
    float introBoxTop = introBox.getGlobalBounds().top;
    game.name.setOrigin(game.name.getGlobalBounds().width / 2, game.name.getGlobalBounds().height);
    game.name.setPosition(introBox.getPosition().x, introBoxTop + curRow * rowHeight + 30);
    ctx->window->getRenderWindow()->draw(game.name);
    curRow += 3;
    game.author.setFont(font);
    game.author.setCharacterSize(24);
    game.author.setOrigin(game.author.getGlobalBounds().width / 2, game.author.getGlobalBounds().height / 2);
    game.author.setPosition(introBox.getPosition().x, introBoxTop + curRow * rowHeight);
    ctx->window->getRenderWindow()->draw(game.author);
    ++curRow;
    game.language.setFont(font);
    game.language.setCharacterSize(24);
    game.language.setOrigin(game.language.getGlobalBounds().width / 2, game.language.getGlobalBounds().height / 2);
    game.language.setPosition(introBox.getPosition().x, introBoxTop + curRow * rowHeight);
    ctx->window->getRenderWindow()->draw(game.language);
    curRow += 2;
    
    for (int i = 0; i < game.mappings.size(); ++i) {
        sf::Text text;
        text.setString(game.mappings[i]);
        text.setFont(font);
        text.setCharacterSize(24);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
        text.setPosition(introBox.getPosition().x, introBoxTop + curRow * rowHeight);
        ctx->window->getRenderWindow()->draw(text);
        ++curRow;
    }
    ++curRow;
    
    for (int i = 0; i < game.instructions.size(); ++i) {
        sf::Text text;
        text.setString(game.instructions[i]);
        text.setFont(font);
        text.setCharacterSize(24);
        text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
        text.setPosition(introBox.getPosition().x, introBoxTop + curRow * rowHeight);
        ctx->window->getRenderWindow()->draw(text);
        ++curRow;
    }
    ++curRow;
    
    sf::Text text;
    text.setString("Press " + game.startButton + " to start");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(introBox.getPosition().x, introBoxTop + introBox.getGlobalBounds().height - rowHeight * 2);
    ctx->window->getRenderWindow()->draw(text);
    
    text.setString("Press the Control Button to go back to the menu");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(introBox.getPosition().x, introBoxTop + introBox.getGlobalBounds().height - rowHeight);
    ctx->window->getRenderWindow()->draw(text);
}

void State_Instructions::setGame(Game & game) {
    this->game = game;
}

void State_Instructions::startGame(BindingDetails * details) {
    if (details->keyCode == 27) {
        std::cout << "starting player 1 game" << std::endl;
        std::string path = game.exePath;
        system(("cd ../../games/" + path + " && " + game.start1).c_str());
    } else if (details->keyCode == 28) {
        std::cout << "starting player 2 game" << std::endl;
        std::string path = game.exePath;
        system(("cd ../../games/" + path + " && " + game.start2).c_str());
    }
}

void State_Instructions::backToMenu(BindingDetails * details) {
    ctx->stateMachine->changeState(StateType::DIYACMenu);
}
