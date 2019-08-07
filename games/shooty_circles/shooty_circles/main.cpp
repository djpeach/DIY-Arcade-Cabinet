#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <tuple>

#include <SFML/Graphics.hpp>

int main() {
    
    std::srand((unsigned int)time(nullptr));
    
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "");
    sf::Vector2u windowSize = window.getSize();
    
    int hmBases = 1;
    int currentBase = 0;
    
    sf::Texture bases[hmBases];
    
    for(int i=0;i<hmBases;i++) {
        std::string rootBasePath = "base";
        std::string extensionBasePath = ".png";
        std::string fullBasePath = rootBasePath + std::to_string(i) + extensionBasePath;
        if (!bases[i].loadFromFile(fullBasePath)) {
            std::cout << "texture could not be loaded from " << fullBasePath << std::endl;
            return 1;
        }
    }
    
    sf::Sprite base;
    base.setTexture(bases[currentBase]);
    base.scale(5, 5);
    sf::FloatRect baseLocalBounds = base.getLocalBounds();
    base.setOrigin(baseLocalBounds.width / 2, baseLocalBounds.height / 2);
    base.setPosition(windowSize.x / 2, windowSize.y / 2);
    
    int hmEnemies = 60;
    using direction = std::tuple<int, int>;
    
    sf::CircleShape enemies[hmEnemies];
    direction enemyDirections[hmEnemies];
    
    enum class Side { Left, Right, Top, Bottom };
    Side xSides[2] = { Side::Left, Side::Right };
    Side ySides[2] = { Side::Top, Side::Bottom };
    
    enum class Direction { Left, Right, Up, Down };
    
    for (int i=0;i<hmEnemies;i++) {
        Side xSide = xSides[std::rand() % 2];
        Side ySide = ySides[std::rand() % 2];
        int initX = (xSide == Side::Left ? -(std::rand() % 10000 + 30) : std::rand() % 10000 + windowSize.x);
        int initY = (ySide == Side::Top ? -(std::rand() % 10000 + 30) : std::rand() % 10000 + windowSize.y);
        int dirX = (xSide == Side::Left ? 1 : -1);
        int dirY = (ySide == Side::Top ? 1 : -1);
        direction dir = std::make_tuple(dirX, dirY);
        sf::CircleShape circle(std::rand() % 22 + 8);
        int r = std::rand() % 256;
        int g = std::rand() % 256;
        int b = std::rand() % 256;
        circle.setFillColor(sf::Color(r, g, b));
        circle.setPosition(initX, initY);
        enemies[i] = circle;
        enemyDirections[i] = dir;
    }
    
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed: {
                    switch (event.key.code) {
                        case sf::Keyboard::Num1:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        
        for (int i=0;i<hmEnemies;i++) {
            direction dir = enemyDirections[i];
            float xSpeed = std::rand()/(float)RAND_MAX / 3;
            float ySpeed = std::rand()/(float)RAND_MAX / 3;
            enemies[i].move(xSpeed * std::get<0>(dir), ySpeed * std::get<1>(dir));
            
        }
        
        window.clear(sf::Color::White);
        window.draw(base);
        for(int i=0;i<hmEnemies;i++) {
            window.draw(enemies[i]);
        }
        window.display();
    }
}
