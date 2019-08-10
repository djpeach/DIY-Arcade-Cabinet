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
    for(int i = 0; i < greens.size(); i++){
        sf::CircleShape greenBall(25);
        greenBall.setFillColor(sf::Color(27,128,37));
        greenBall.setOrigin(25, 25);
        greenBall.setPosition(greens[i].position.x, greens[i].position.y);
        window.draw(greenBall);
    }

    for(int i = 0; i < reds.size(); i++){
        sf::CircleShape redBall(15);
        redBall.setFillColor(sf::Color(204,39,10));
        redBall.setOrigin(15, 15);
        redBall.setPosition(reds[i].position.x, reds[i].position.y);
        window.draw(redBall);
    }
};

void Level::registerCollisions( sf::Vector2f & userPosition, int userRadius ){
    for(int i = 0; i < greens.size(); i++){

        int addRad = 25 + userRadius;
        int diffX = abs(userPosition.x - greens[i].position.x);
        int diffY = abs(userPosition.y - greens[i].position.y);

        std::cout << addRad << std::endl;
        std::cout << diffX << std::endl;
        std::cout << diffY << std::endl;

        if ( (diffX < addRad) && (diffY < addRad)){
            greens[i].collision = true;
            std::cout << "Hit green" << std::endl;


        }
    }

    for(int i = 0; i < reds.size(); i++){

        int addRad = 25 + userRadius;
        int diffX = abs(userPosition.x - reds[i].position.x);
        int diffY = abs(userPosition.y - reds[i].position.y);

        if ( (diffX < addRad) && (diffY < addRad)){
            reds[i].collision = true;
            std::cout << "Hit red" << std::endl;
            
        }
    }
}









