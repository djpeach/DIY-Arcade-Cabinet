#include <SFML/Graphics.hpp>

int main() {

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const float SCREEN_W = desktopMode.width;
    const float SCREEN_H = desktopMode.height;
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Bumpy Circles", sf::Style::Fullscreen);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

          switch (event.type) {

            case sf::Event::Closed:
              window.close();
              break;

            default:
              // std::cout << "Unknown event" << std::endl;
              break;
          }
        }

        window.clear();

        window.display();

    }
}
