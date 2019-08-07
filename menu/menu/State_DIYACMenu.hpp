#pragma once

#include "State_Base.hpp"
#include "EventManager.hpp"

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
};
