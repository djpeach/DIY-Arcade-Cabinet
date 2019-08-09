#pragma once

#include <vector>

#include "State_Base.hpp"
#include "EventManager.hpp"

struct Game {
    Game() {
        clear();
    }
    
    sf::Text name;
    std::string exePath;
    std::string start1;
    std::string start2;
    sf::Color bgColor;
    
    void clear() {
        name.setString("");
        exePath = "";
        start1 = "";
        start2 = "";
        bgColor = sf::Color(120, 120, 120);
    }
};

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
    void startGame(BindingDetails * details);
    
private:
    
    void getGames();
    
    std::vector<Game> games;
    std::vector<sf::RectangleShape> gameTiles;
    sf::RectangleShape selectedTileHighlight;
    int selectedTile;
    sf::Vector2f windowGrid, tileSize;
    sf::Vector2i tiles;
};
