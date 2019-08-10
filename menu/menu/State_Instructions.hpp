#pragma once

#include <vector>

#include "State_Base.hpp"
#include "EventManager.hpp"

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
    
private:
};
