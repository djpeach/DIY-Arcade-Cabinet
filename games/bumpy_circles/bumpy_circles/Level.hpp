#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>


struct Circle {
    Circle(sf::Vector2f speed, sf::Vector2f position, int size) : speed(speed), exists(true), collision(false), ball((float)size) {
        ball.setPosition(position);
    }
    sf::Vector2f speed;
    bool exists, collision;
    sf::CircleShape ball;
};

class Level{
    public:
        Level(int maxTime, int numberGreens, int numberReds, int greenMaxSpeed, int redMaxSpeed);

        ~Level(){};

        void registerCollisions(sf::Vector2f & userPosition, int userRadius);
        void handleCollisions();
        void update(sf::Time dt);
        void draw(sf::RenderWindow & window);

        bool cleared = false;

    private:
        std::vector<Circle> greens, reds;
        sf::Clock elapsed;
        int numberGreens, numberReds, greenMaxSpeed, redMaxSpeed, maxScoreTime, X, Y, speedX, speedY;

        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

};