#pragma once

#include <vector>

#include "State_Base.hpp"
#include "EventManager.hpp"
#include "Game.hpp"

class State_Instructions : public State_Base {

public:
    State_Instructions(SharedContext * ctx);
    ~State_Instructions();

    void onCreate();
    void onDestroy();

    void activate();
    void deactivate();

    void update(const sf::Time & delta);
    void draw();

    void setGame(Game & game);
    void startGame(BindingDetails * details);
    void backToMenu(BindingDetails * details);

private:
    sf::RectangleShape introBox;
    Game game;
    bool canStartGame;
    bool drewLoading;
};
