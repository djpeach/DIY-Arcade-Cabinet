#pragma once

#include <iostream>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "SharedContext.hpp"

struct SharedContext;

class DIYACMenu {
    
public:
    DIYACMenu();
    ~DIYACMenu();
    
    const sf::Time getMenuDeltaTime();
    bool isOpen();
    
    void update();
    void render();
    void lateUpdate();
    
private:
    void restartClock();
    
    bool closed;
    sf::Clock clock;
    sf::Time menuDeltaTime;
    SharedContext ctx;
};
