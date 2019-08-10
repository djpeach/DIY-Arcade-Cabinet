#include "Level.hpp"
#include <iostream>

Level::Level(int maxTime, int numberGreens, int numberReds, int greenMaxSpeed, int redMaxSpeed) : maxScoreTime(maxTime), numberGreens(numberGreens), numberReds(numberReds), greenMaxSpeed(greenMaxSpeed), redMaxSpeed(redMaxSpeed){
    static bool seeded = false;
    if(!seeded) {
        srand(time(NULL));
        seeded = true;
    }
    
    for (int i = 0; i < numberGreens; i++){
        if (greenMaxSpeed != 0){
            speedX = rand() % greenMaxSpeed + 1;
        }else{
            speedX = 0;
        }

        speedY = greenMaxSpeed - speedX;
        
        X = rand() % desktopMode.width;
        Y = rand() % desktopMode.height;
        

        sf::Vector2f speed = sf::Vector2f(speedX, speedY);
        sf::Vector2f position = sf::Vector2f(X, Y);

        Circle green(speed, position);
        greens.push_back(green);

    }

    for (int i = 0; i < numberReds; i++){

        if (redMaxSpeed != 0){
            speedX = rand() % redMaxSpeed + 1;
        }else{
            speedX = 0;
        }

        speedY = redMaxSpeed - speedX;

        X = rand() % desktopMode.width;
        Y = rand() % desktopMode.height;
        

        sf::Vector2f speed = sf::Vector2f(speedX, speedY);
        sf::Vector2f position = sf::Vector2f(X, Y);

        Circle red(speed, position);
        reds.push_back(red);
    }
};

void Level::draw(sf::RenderWindow & window){
    for(int i; i < greens.size(); i++){
        sf::CircleShape greenBall(25);
        greenBall.setFillColor(sf::Color(27,128,37));
        greenBall.setOrigin(25, 25);
        greenBall.setPosition(greens[i].position.x, greens[i].position.y);
        window.draw(greenBall);
    }

    for(int i; i < reds.size(); i++){
        sf::CircleShape redBall(25);
        redBall.setFillColor(sf::Color(27,128,37));
        redBall.setOrigin(25, 25);
        redBall.setPosition(reds[i].position.x, reds[i].position.y);
        window.draw(redBall);
    }
};









