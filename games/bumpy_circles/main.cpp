#include <SFML/Graphics.hpp>

int main() {

    sf::Time dt;
    sf::Clock speedClock;
    sf::Clock gameClock;


    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const float SCREEN_W = desktopMode.width;
    const float SCREEN_H = desktopMode.height;
    int changeX = 0;
    int changeY = 0;

    const int USER_R = 50;
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Bumpy Circles", sf::Style::Fullscreen);

    /*
     CIRCLE SHAPE
     */
    sf::CircleShape circle(USER_R);
    
    // radius and point count can be set after as well
    //shape.setRadius(100);
    //shape.setPointCount(3);
    
    // Red, Green and Blue from 0 to 255
    circle.setFillColor(sf::Color(66,135,245));
    circle.setOrigin(50,50);

    circle.setPosition(SCREEN_W/2, SCREEN_H/2);

    while (window.isOpen()) {
        dt += clock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event)) {

          switch (event.type) {

            case sf::Event::Closed:
              window.close();
              break;

            case sf::Event::KeyPressed:
              switch (event.key.code){
                case sf::Keyboard::Slash:
                  window.close();
                  break;

                case sf::Keyboard::W:
                  changeY = -10;
                  circle.move(0, changeY);
                  break;

                case sf::Keyboard::S:
                  changeY = +10;
                  circle.move(0, changeY);
                  break;

                case sf::Keyboard::A:
                  changeX = -10;
                  circle.move(changeX, 0);
                  break;
                
                case sf::Keyboard::D:
                  changeX = +10;
                  circle.move(changeX, 0);
                  break;

                default:
                  break;
              }

            default:
              // std::cout << "Unknown event" << std::endl;
              break;
          }
        }

        window.clear();

        window.draw(circle);

        if(dt > (1/60)){
          window.update();
        }

        window.display();

    }
}
