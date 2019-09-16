#pragma once

#include <vector>

#include "State_Base.hpp"
#include "EventManager.hpp"

class State_Alert : public State_Base {

public:
    State_Alert(SharedContext * ctx);
    ~State_Alert();

    void onCreate();
    void onDestroy();

    void activate();
    void deactivate();

    void update(const sf::Time & delta);
    void draw();

    void setGameMode(std::string mode);
    void backToMenu(BindingDetails * details);

private:
    sf::RectangleShape alertBox;
    std::string mode;
};
