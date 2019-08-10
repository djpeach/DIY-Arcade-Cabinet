#include "Level.hpp"

Level::Level(int maxTime, int numberGreens, int numberReds, int greenMaxSpeed, int redMaxSpeed) : maxScoreTime(maxTime), numberGreens(numberGreens), numberReds(numberReds), greenMaxSpeed(greenMaxSpeed), redMaxSpeed(redMaxSpeed){
    for (int i = 0; i <= numberGreens; i++){
        speedX = rand() % greenMaxSpeed + 1;
        speedY = greenMaxSpeed - speedX;
        
        X = rand() % desktopMode.width;
        Y = rand() % desktopMode.height;
        

        sf::Vector2f speed = sf::Vector2f(speedX, speedY);
        sf::Vector2f position = sf::Vector2f(X, Y);

        Circle green(sf::Color::Green, speed, position);
        greens.push_back(green);

    }

    for (int i = 0; i <= numberReds; i++){
        int redX = rand() % redMaxSpeed + 1;
        int redY = redMaxSpeed - redX;

        X = rand() % desktopMode.width;
        Y = rand() % desktopMode.height;
        

        sf::Vector2f speed = sf::Vector2f(speedX, speedY);
        sf::Vector2f position = sf::Vector2f(X, Y);

        Circle red(sf::Color::Red, speed, position);
        reds.push_back(red);
    }
};



