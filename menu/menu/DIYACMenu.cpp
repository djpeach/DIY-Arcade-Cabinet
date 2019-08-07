#include "DIYACMenu.hpp"
#include "StateMachine.cpp"

DIYACMenu::DIYACMenu() {
    ctx.window = new Window(&ctx);
    ctx.eventManager = new EventManager(&ctx);
    ctx.stateMachine = new StateMachine(&ctx);
    closed = false;
}

DIYACMenu::~DIYACMenu() {
    delete ctx.window;
    delete ctx.eventManager;
    delete ctx.stateMachine;
}

const sf::Time DIYACMenu::getMenuDeltaTime() {
    return menuDeltaTime;
}

bool DIYACMenu::isOpen() {
    return !closed;
}

void DIYACMenu::update() {
    ctx.window->pollEvents();
    ctx.eventManager->handleRealTimeEvents();
}

void DIYACMenu::render() {
    ctx.window->clear();
    
    //            draw to screen           //
    /* =================================== */
    
    
    
    /* =================================== */
    
    ctx.window->display();
}

void DIYACMenu::lateUpdate() {
    restartClock();
}

void DIYACMenu::restartClock() {
    menuDeltaTime = clock.restart();
}
