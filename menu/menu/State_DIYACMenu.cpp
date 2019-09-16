#include "State_DIYACMenu.hpp"
#include "SharedContext.hpp"

#include <string>

State_DIYACMenu::State_DIYACMenu(SharedContext * ctx) : State_Base(ctx), games() {}
State_DIYACMenu::~State_DIYACMenu() {}

void State_DIYACMenu::onCreate() {

    if (ctx->stateMachine->hasState(StateType::Instructions)) {
        ctx->stateMachine->remove(StateType::Instructions);
    }

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
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player1Go", &State_DIYACMenu::openGame, this);
    ctx->eventManager->addCallback(StateType::DIYACMenu, "player2Go", &State_DIYACMenu::openGame, this);

    view.setCenter(windowSize.x / 2, windowSize.y / 2);
    ctx->window->getRenderWindow()->setView(view);
}

void State_DIYACMenu::onDestroy() {
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player1MoveRight");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player1MoveLeft");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player1MoveUp");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player1MoveDown");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player2MoveRight");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player2MoveLeft");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player2MoveUp");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player2MoveDown");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player1Go");
    ctx->eventManager->removeCallback(StateType::DIYACMenu, "player2Go");

}

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
        // ctx->window->getRenderWindow()->draw(games[i].logo);
        sf::Text & title = games[i].name;
        title.setFont(font);
        title.setCharacterSize(32);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        sf::FloatRect tileBounds = gameTiles[i].getGlobalBounds();
        title.setPosition(tileBounds.left + tileBounds.width / 2, tileBounds.top + tileBounds.height + 55);
        ctx->window->getRenderWindow()->draw(title);
    }
}

void State_DIYACMenu::getGames() {
    std::ifstream gamesStream;
    std::string filePath = "../../games/games.cfg";
    gamesStream.open(filePath);

    if (!gamesStream.is_open()){
        std::cerr << "! Failed loading games from file: " << filePath << std::endl;
        exit(1);
    }

    std::string line;
    bool needNewGame = true;
    int curGame = -1;

    while (std::getline(gamesStream, line)){
        if (needNewGame) {
            Game gameToAdd = Game();
            games.push_back(gameToAdd);
            ++curGame;
            needNewGame = false;
        }
        Game & game = games[curGame];

        // std::unique_ptr<sf::Texture> logo;
        // logo->loadFromFile("assets/images/logo.png");
        // game.logoTexture = std::move(logo);
        // game.logo.setTexture(*game.logoTexture);

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
        } else if (type == "AUTHOR") {
            std::string author;
            std::getline(lineStream, author);
            game.author.setString(author);
        } else if (type == "LANGUAGE") {
            std::string language;
            std::getline(lineStream, language);
            game.language.setString(language);
        } else if (type == "MAPPING") {
            std::string mapping;
            std::string desc;
            std::string control;
            std::getline(lineStream, mapping);
            mapping = mapping.substr(1, mapping.length());
            desc = mapping.substr(0, mapping.find(":"));
            control = mapping.substr(mapping.find(":") + 1, mapping.length());
            game.mappings.push_back("To " + desc + ", press " + translateControlToButton(control));
        } else if (type == "INSTRUCTION") {
            std::string instruction;
            std::getline(lineStream, instruction);
            instruction = instruction.substr(1, instruction.length());
            game.instructions.push_back(instruction);
        } else if (type == "END_GAME_ENTRY") {
            needNewGame = true;
        }

    }
    gamesStream.close();
}

std::string State_DIYACMenu::translateControlToButton(std::string & control) {
    std::unordered_map<std::string, std::string> mappings ({
        {"Slash", "Control Button"},
        {"Num1", "Player 1 Start"},
        {"Num2", "Player 2 Start"},
        {"W", "Player 1 Up"},
        {"A", "Player 1 Left"},
        {"S", "Player 1 Down"},
        {"D", "Player 1 Right"},
        {"I", "Player 2 Up"},
        {"J", "Player 2 Left"},
        {"K", "Player 2 Down"},
        {"L", "Player 2 Right"},
        {"F", "Player 1 Red"},
        {"E", "Player 1 White"},
        {"Q", "Player 1 Blue"},
        {"Z", "Player 1 Yellow"},
        {"X", "Player 1 Green"},
        {"C", "Player 1 Blue"},
        {"H", "Player 1 Red"},
        {"U", "Player 1 White"},
        {"O", "Player 1 Blue"},
        {"B", "Player 1 Yellow"},
        {"N", "Player 1 Green"},
        {"M", "Player 1 Blue"},
    });

    return mappings[control];
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

void State_DIYACMenu::openGame(BindingDetails * details) {
    if (details->keyCode == 27) {
      if (games[selectedTile - 1].start1 == "") {
        ctx->stateMachine->changeState(StateType::Alert);
        dynamic_cast<State_Alert *>(ctx->stateMachine->getCurrentState())->setString(games[selectedTile - 1].name.getString() + " does not support 1 player mode");
      } else {
        games[selectedTile - 1].startButton = "Player 1 Start";
        ctx->stateMachine->changeState(StateType::Instructions);
        dynamic_cast<State_Instructions *>(ctx->stateMachine->getCurrentState())->setGame(games[selectedTile - 1]);
      }
    } else if (details->keyCode == 28) {
      if (games[selectedTile - 1].start2 == "") {
        ctx->stateMachine->changeState(StateType::Alert);
        dynamic_cast<State_Alert *>(ctx->stateMachine->getCurrentState())->setString(games[selectedTile - 1].name.getString() + " does not support 2 player mode");
      } else {
        games[selectedTile - 1].startButton = "Player 2 Start";
        ctx->stateMachine->changeState(StateType::Instructions);
        dynamic_cast<State_Instructions *>(ctx->stateMachine->getCurrentState())->setGame(games[selectedTile - 1]);
      }
    }
}
