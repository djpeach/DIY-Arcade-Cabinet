#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>


struct Circle {
    Circle(sf::Vector2f speed, sf::Vector2f position) : speed(speed), position(position), exists(false), collision(false) {}
    sf::Vector2f speed, position;
    bool exists, collision;
};

class Level{
    public:
        Level(int maxTime, int numberGreens, int numberReds, int greenMaxSpeed, int redMaxSpeed);

        ~Level(){};

        void update(sf::RenderWindow & window);
        void draw(sf::RenderWindow & window);
        void registerCollisions(sf::Vector2f & userPosition, int userRadius);

    private:
        std::vector<Circle> greens, reds;
        sf::Clock elapsed;
        int numberGreens, numberReds, greenMaxSpeed, redMaxSpeed, maxScoreTime, X, Y, speedX, speedY;
        bool greenCollisions, redCollisions;
        bool cleared = false;

        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

        void handleCollisions();

};