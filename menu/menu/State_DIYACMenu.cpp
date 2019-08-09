#include "State_DIYACMenu.hpp"
#include "SharedContext.hpp"

#include <string>
#include "stdlib.h"

State_DIYACMenu::State_DIYACMenu(SharedContext * ctx) : State_Base(ctx), games() {}
State_DIYACMenu::~State_DIYACMenu() {}

void State_DIYACMenu::onCreate() {
    
    getGames();
    
    selectedTile = 1;
    
    sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
    windowGrid.x = windowSize.x / 13;
    windowGrid.y = windowSize.y / 7;
    tiles.x = 3;
    tiles.y = 2;
    tileSize.x = windowGrid.x * tiles.x;
    tileSize.y = windowGrid.y * tiles.y;
    
    for (int i=0; i<games.size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(windowGrid.x * tiles.x, windowGrid.y * tiles.y));
        rect.setPosition((((tiles.x + 1) * (i % tiles.x)) + 1) * windowGrid.x, (((tiles.y + 1) * (i / (tiles.y + 1)) + 1)) * windowGrid.y);
        rect.setFillColor(games[i].bgColor);
        std::cout << std::string(games[i].name.getString()) << std::endl;
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Could not load font from assets/fonts/arial.ttf" << std::endl;
            exit(1);
        }
        sf::Text & title = games[i].name;
        title.setFont(font);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        title.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);
        
        gameTiles.push_back(rect);
    }
    
    selectedTileHighlight.setSize(sf::Vector2f(windowGrid.x * tiles.x, windowGrid.y * tiles.y));
    selectedTileHighlight.setFillColor(sf::Color(200, 200, 200));
    selectedTileHighlight.setOrigin(selectedTileHighlight.getSize().x / 2, selectedTileHighlight.getSize().y / 2);
    selectedTileHighlight.scale(1.1, 1.1);
    
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveRight", &State_DIYACMenu::moveRight, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveLeft", &State_DIYACMenu::moveLeft, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveUp", &State_DIYACMenu::moveUp, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1MoveDown", &State_DIYACMenu::moveDown, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveRight", &State_DIYACMenu::moveRight, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveLeft", &State_DIYACMenu::moveLeft, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveUp", &State_DIYACMenu::moveUp, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2MoveDown", &State_DIYACMenu::moveDown, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "startGame", &State_DIYACMenu::startGame, this);
    
    view.setCenter(windowSize.x / 2, windowSize.y / 2);
    ctx->window->getRenderWindow()->setView(view);
}

void State_DIYACMenu::onDestroy() {}

void State_DIYACMenu::activate() {}
void State_DIYACMenu::deactivate() {}

void State_DIYACMenu::update(const sf::Time & delta) {
    selectedTileHighlight.setPosition(((((tiles.x + 1) * ((selectedTile - 1) % tiles.x)) + 1) * windowGrid.x + (gameTiles[0].getSize().x / 2)), (((tiles.y + 1) * ((selectedTile - 1) / (tiles.y + 1)) + 1)) * windowGrid.y + (gameTiles[0].getSize().y / 2));
    sf::FloatRect windowViewSpace = ctx->window->getViewSpace();
    if (selectedTileHighlight.getPosition().y > windowViewSpace.top + windowViewSpace.height) {
            sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
            view.setCenter(windowSize.x / 2, view.getCenter().y + (windowSize.y / 7 * 3));
            ctx->window->getRenderWindow()->setView(view);
    } else if (selectedTileHighlight.getPosition().y < windowViewSpace.top) {
        sf::Vector2u windowSize = ctx->window->getRenderWindow()->getSize();
        view.setCenter(windowSize.x / 2, view.getCenter().y - (windowSize.y / 7 * 3));
        ctx->window->getRenderWindow()->setView(view);
    }
}
void State_DIYACMenu::draw() {
    ctx->window->getRenderWindow()->draw(selectedTileHighlight);
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Could not load font from assets/fonts/arial.ttf" << std::endl;
        exit(1);
    }
    for (int i=0; i<games.size(); ++i) {
        ctx->window->getRenderWindow()->draw(gameTiles[i]);
        games[i].name.setFont(font);
        ctx->window->getRenderWindow()->draw(games[i].name);
    }
}

void State_DIYACMenu::getGames() {
    std::ifstream gamesStream;
    std::string filePath = "/Users/danielpeach/Dev/DIY-Arcade-Cabinet/games/games.cfg";
    gamesStream.open(filePath);
    
    if (!gamesStream.is_open()){
        std::cerr << "! Failed loading games from file: " << filePath << std::endl;
        exit(1);
    }
    
    std::string line;
    Game game;
    
    while (std::getline(gamesStream, line)){
        
        if (line[0] == '#' || line.empty()) { continue; }
        
        std::stringstream lineStream(line);
        std::string type;
        lineStream >> type;
        
        if (type == "NAME") {
            std::string name;
            std::getline(lineStream, name);
            name = name.substr(1, name.length());
            game.name.setString(name);
        } else if (type == "EXE_PATH") {
            std::string exePath;
            std::getline(lineStream, exePath);
            exePath = exePath.substr(1, exePath.length());
            game.exePath = exePath;
        } else if (type == "START1") {
            std::string start1;
            std::getline(lineStream, start1);
            start1 = start1.substr(1, start1.length());
            game.start1 = start1;
        } else if (type == "START2") {
            std::string start2;
            std::getline(lineStream, start2);
            start2 = start2.substr(1, start2.length());
            game.start2 = start2;
        } else if (type == "BG_COLOR") {
            std::string r, g, b;
            lineStream >> r >> g >> b;
            game.bgColor = sf::Color(stoi(r), stoi(g), stoi(b));
        } else if (type == "END_GAME_ENTRY") {
            games.push_back(game);
            game.clear();
        }
        
    }
    gamesStream.close();
}

void State_DIYACMenu::showAlert(BindingDetails * details) {}

void State_DIYACMenu::moveRight(BindingDetails * details) {
    if (selectedTile < games.size()) {
        ++selectedTile;
    }
}

void State_DIYACMenu::moveLeft(BindingDetails * details) {
    if (selectedTile > 1) {
        --selectedTile;
    }
}

void State_DIYACMenu::moveUp(BindingDetails * details) {
    if (selectedTile - tiles.x > 0) {
        selectedTile -= tiles.x;
    }
}
void State_DIYACMenu::moveDown(BindingDetails * details) {
    if (selectedTile + tiles.x <= games.size()) {
        selectedTile += tiles.x;
    } else {
        selectedTile = games.size();
    }
}

void State_DIYACMenu::startGame(BindingDetails * details) {
    std::string path = games[selectedTile - 1].exePath;
    system(("cd ../../games/" + path + " && " + games[selectedTile - 1].start1).c_str());
}
