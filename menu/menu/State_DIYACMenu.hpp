#pragma once

#include "State_Base.hpp"
#include "EventManager.hpp"

struct Game {
    Game(const std::string & name) : name(name) {}
    std::string name;
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
    
private:
    sf::RectangleShape gameTiles[13];
    sf::RectangleShape selectedTileHighlight;
};
