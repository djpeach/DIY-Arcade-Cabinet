#include "Window.hpp"
#include "SharedContext.hpp"

Window::Window(SharedContext * ctx) : ctx(ctx) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    // renderWindow.create(sf::VideoMode(desktopMode.width, desktopMode.height), "DIY Arcade Menu", sf::Style::Fullscreen);
    renderWindow.create(sf::VideoMode(1280, 1024), "DIY Arcade Menu");
}

Window::~Window() {
    renderWindow.close();
}

void Window::pollEvents() {
    sf::Event event;
    while(renderWindow.pollEvent(event)) {
        ctx->eventManager->handlePolledEvent(event);
    }
}

sf::RenderWindow * Window::getRenderWindow() {
    return &renderWindow;
}

sf::FloatRect Window::getViewSpace(){
    sf::Vector2f viewCenter(renderWindow.getView().getCenter());
    sf::Vector2f viewSize(renderWindow.getView().getSize());
    sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    return viewSpace;
}

void Window::clear() {
    renderWindow.clear(sf::Color(50, 50, 50));
}

void Window::display() {
    renderWindow.display();
}
