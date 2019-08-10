#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Bumpy Circles", sf::Style::Fullscreen);

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
