#pragma once

#include <vector>

#include "State_Base.hpp"
#include "EventManager.hpp"
#include "Game.hpp"

class State_DIYACMenu : public State_Base {
    
public:
    State_DIYACMenu(SharedContext * ctx);
    ~State_DIYACMenu();
    
    void onCreate();
    void onDestroy();
    
    void activate();
    void deactivate();
    
    void update(const sf::Time & delta);
    void draw();
    
    void showAlert(BindingDetails * details);
    void moveRight(BindingDetails * details);
    void moveLeft(BindingDetails * details);
    void moveUp(BindingDetails * details);
    void moveDown(BindingDetails * details);
    void openGame(BindingDetails * details);
    
private:
    
    void getGames();
    std::string translateControlToButton(std::string & control);
    
    std::vector<Game> games;
    std::vector<sf::RectangleShape> gameTiles;
    sf::RectangleShape selectedTileHighlight;
    int selectedTile;
    sf::Vector2f windowGrid, tileSize;
    sf::Vector2i tiles;
    bool startingGame;
    sf::Time startedGameTime;
    sf::Clock clock;
};
