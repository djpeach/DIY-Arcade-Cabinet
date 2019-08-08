#include "State_DIYACMenu.hpp"
#include "SharedContext.hpp"

State_DIYACMenu::State_DIYACMenu(SharedContext * ctx) : State_Base(ctx) {}
State_DIYACMenu::~State_DIYACMenu() {}

void State_DIYACMenu::onCreate() {
    Game games[13] = { Game("game1"), Game("game2"), Game("game3"), Game("game4"), Game("game5"), Game("game6"), Game("game7"), Game("game8"), Game("game9"), Game("game10"), Game("game11"), Game("game12"), Game("game13") };
    
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    sf::Vector2f windowGrid, tileSize;
    sf::Vector2i tiles;
    windowGrid.x = windowSize.x / 13;
    windowGrid.y = windowSize.y / 7;
    tiles.x = 3;
    tiles.y = 2;
    tileSize.x = windowGrid.x * tiles.x;
    tileSize.y = windowGrid.y * tiles.y;
    
    for (int i=0; i<13; ++i) {
        sf::RectangleShape rect(sf::Vector2f(windowGrid.x * tiles.x, windowGrid.y * tiles.y));
        rect.setPosition((((tiles.x + 1) * (i % tiles.x)) + 1) * windowGrid.x, (((tiles.y + 1) * (i / (tiles.y + 1)) + 1)) * windowGrid.y);
        if (i < 3) {
            rect.setFillColor(sf::Color::Red);
        } else if ( i < 6) {
            rect.setFillColor(sf::Color::Yellow);
        } else if ( i < 9) {
            rect.setFillColor(sf::Color::Green);
        } else if ( i < 12) {
            rect.setFillColor(sf::Color::Blue);
        } else if ( i < 15) {
            rect.setFillColor(sf::Color::Black);
        }
        gameTiles[i] = rect;
    }
    
    selectedTileHighlight.setSize(sf::Vector2f(windowGrid.x * tiles.x, windowGrid.y * tiles.y));
    selectedTileHighlight.setFillColor(sf::Color(200, 200, 200));
    selectedTileHighlight.setOrigin(selectedTileHighlight.getSize().x / 2, selectedTileHighlight.getSize().y / 2);
    selectedTileHighlight.setPosition(windowGrid.x + gameTiles[0].getSize().x / 2, windowGrid.y + gameTiles[0].getSize().y / 2);
    selectedTileHighlight.scale(1.1, 1.1);
    
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveRight", &State_DIYACMenu::moveRight, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveLeft", &State_DIYACMenu::moveLeft, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveUp", &State_DIYACMenu::moveUp, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveDown", &State_DIYACMenu::moveDown, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveRight", &State_DIYACMenu::moveRight, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveLeft", &State_DIYACMenu::moveLeft, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveUp", &State_DIYACMenu::moveUp, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveDown", &State_DIYACMenu::moveDown, this);
    
    view.setCenter(windowSize.x / 2, windowSize.y / 2);
    ctx->window->getRenderWindow()->setView(view);
}

void State_DIYACMenu::onDestroy() {}

void State_DIYACMenu::activate() {}
void State_DIYACMenu::deactivate() {}

void State_DIYACMenu::update(const sf::Time & delta) {}
void State_DIYACMenu::draw() {
    ctx->window->getRenderWindow()->draw(selectedTileHighlight);
    for (int i=0; i<13; ++i) {
        ctx->window->getRenderWindow()->draw(gameTiles[i]);
    }
}

void State_DIYACMenu::showAlert(BindingDetails * details) {}
void State_DIYACMenu::moveRight(BindingDetails * details) {
    std::cout << "moving right" << std::endl;
}
void State_DIYACMenu::moveLeft(BindingDetails * details) {}
void State_DIYACMenu::moveUp(BindingDetails * details) {
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    view.setCenter(windowSize.x / 2, view.getCenter().y - (windowSize.y / 7 * 3));
    ctx->window->getRenderWindow()->setView(view);
}
void State_DIYACMenu::moveDown(BindingDetails * details) {
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    view.setCenter(windowSize.x / 2, view.getCenter().y + (windowSize.y / 7 * 3));
    ctx->window->getRenderWindow()->setView(view);
}
