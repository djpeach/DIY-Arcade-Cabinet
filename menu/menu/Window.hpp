#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct SharedContext;

class Window {
    
public:
    Window(SharedContext * ctx);
    ~Window();
    
    sf::RenderWindow * getRenderWindow();
    sf::FloatRect getViewSpace();
    
    void pollEvents();
    void clear();
    void display();
    
private:
    sf::RenderWindow renderWindow;
    SharedContext * ctx;
};
