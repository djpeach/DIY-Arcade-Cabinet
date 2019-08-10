#include "DIYACMenu.hpp"

DIYACMenu::DIYACMenu() {
    ctx.window = new Window(&ctx);
    ctx.eventManager = new EventManager(&ctx);
    ctx.stateMachine = new StateMachine(&ctx);
    closed = false;
    
    ctx.eventManager->addCallback(StateType(0), "closeWindow", &DIYACMenu::closeWindow, this);
    ctx.eventManager->addCallback(StateType::DIYACMenu, "slashClose", &DIYACMenu::closeWindow, this);
    
    ctx.stateMachine->changeState(StateType::DIYACMenu);
}

DIYACMenu::~DIYACMenu() {
    delete ctx.stateMachine;
    delete ctx.window;
    delete ctx.eventManager;
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
    ctx.stateMachine->update(menuDeltaTime);
}

void DIYACMenu::render() {
    ctx.window->clear();
    
    ctx.stateMachine->draw();
    
    ctx.window->display();
}

void DIYACMenu::lateUpdate() {
    ctx.stateMachine->processRequests();
    restartClock();
}

void DIYACMenu::closeWindow(BindingDetails * details) {
    closed = true;
}

void DIYACMenu::restartClock() {
    menuDeltaTime = clock.restart();
}
