#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Circle {
    Circle(sf::Color color, sf::Vector2f speed, sf::Vector2f position) : color(color), speed(speed), position(position), exists(false), collision(false) {}
    sf::Color color;
    sf::Vector2f speed, position;
    bool exists, collision;
};

class Level{
    public:
        Level(int maxTime, int numberGreens, int numberReds, int greenMaxSpeed, int redMaxSpeed);

        ~Level(){};

        void update(sf::RenderWindow & window);
        void draw(sf::RenderWindow & window);
        void registerCollisions(sf::FloatRect & userBounds);

    private:
        std::vector<Circle> greens, reds;
        sf::Clock elapsed;
        int numberGreens, numberReds, greenMaxSpeed, redMaxSpeed, maxScoreTime, X, Y, speedX, speedY;
        bool greenCollisions, redCollisions;
        bool cleared = false;

        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

        void handleCollisions();
};