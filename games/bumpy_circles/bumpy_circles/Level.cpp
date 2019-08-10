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

        Circle green(speed, position, 25);
        green.ball.setOrigin(25, 25);
        green.ball.setFillColor(sf::Color(27,128,37));
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

        Circle red(speed, position, 15);
        red.ball.setOrigin(15, 15);
        red.ball.setFillColor(sf::Color(204,39,10));
        reds.push_back(red);
    }
};

void Level::registerCollisions(sf::Vector2f & userPosition, int userRadius){
    for(int i = 0; i < greens.size(); i++){

        int addRad = 25 + userRadius;
        int diffX = abs(userPosition.x - greens[i].ball.getPosition().x);
        int diffY = abs(userPosition.y - greens[i].ball.getPosition().y);

        if ( (diffX < addRad) && (diffY < addRad)){
            greens[i].collision = true;
        }
    }

    for(int i = 0; i < reds.size(); i++){

        int addRad = 25 + userRadius;
        int diffX = abs(userPosition.x - reds[i].ball.getPosition().x);
        int diffY = abs(userPosition.y - reds[i].ball.getPosition().y);

        if ( (diffX < addRad) && (diffY < addRad)){
            reds[i].collision = true;
        }
    }
}

void Level::handleCollisions(){
    int clearedGreens = 0;
    for(int i = 0; i < greens.size(); i++){
        if (greens[i].collision && greens[i].exists){
            greens[i].exists = false;
        } else if (!greens[i].exists) {
            ++clearedGreens;
        }
    }

    if (clearedGreens == greens.size()) {
        cleared = true;
    }

    for(int i = 0; i < reds.size(); i++){
        if (reds[i].collision){
            
        }
    }
}

void Level::update(sf::Time dt){
    for(int i = 0; i < greens.size(); i++){
        if (greens[i].exists) {
            Circle & circle = greens[i];
            if (circle.ball.getPosition().x + circle.speed.x * dt.asSeconds() < circle.ball.getRadius()) {
                circle.ball.setPosition(circle.ball.getRadius(), circle.ball.getPosition().y);
                circle.speed.x *= -1;
            } else {
                circle.ball.move(circle.speed.x * dt.asSeconds(), 0);
            }
            if (circle.ball.getPosition().x + circle.speed.x * dt.asSeconds() > desktopMode.width - circle.ball.getRadius()) {
                circle.ball.setPosition(desktopMode.width - circle.ball.getRadius(), circle.ball.getPosition().y);
                circle.speed.x *= -1;
            } else {
                circle.ball.move(circle.speed.x * dt.asSeconds(), 0);
            }

            if (circle.ball.getPosition().y + circle.speed.y * dt.asSeconds() < circle.ball.getRadius()) {
                circle.ball.setPosition(circle.ball.getPosition().x, circle.ball.getRadius());
                circle.speed.y *= -1;
            } else {
                circle.ball.move(0, circle.speed.y * dt.asSeconds());
            }
            if (circle.ball.getPosition().y + circle.speed.y * dt.asSeconds() > desktopMode.height - circle.ball.getRadius()) {
                circle.ball.setPosition(circle.ball.getPosition().x, desktopMode.height - circle.ball.getRadius());
                circle.speed.y *= -1;
            } else {
                circle.ball.move(0, circle.speed.y * dt.asSeconds());
            }
        }
    }

    for(int i = 0; i < reds.size(); i++){
        if (reds[i].exists) {
            Circle & circle = reds[i];
            if (circle.ball.getPosition().x + circle.speed.x * dt.asSeconds() < circle.ball.getRadius()) {
                circle.ball.setPosition(circle.ball.getRadius(), circle.ball.getPosition().y);
                circle.speed.x *= -1;
            } else {
                circle.ball.move(circle.speed.x * dt.asSeconds(), 0);
            }
            if (circle.ball.getPosition().x + circle.speed.x * dt.asSeconds() > desktopMode.width - circle.ball.getRadius()) {
                circle.ball.setPosition(desktopMode.width - circle.ball.getRadius(), circle.ball.getPosition().y);
                circle.speed.x *= -1;
            } else {
                circle.ball.move(circle.speed.x * dt.asSeconds(), 0);
            }

            if (circle.ball.getPosition().y + circle.speed.y * dt.asSeconds() < circle.ball.getRadius()) {
                circle.ball.setPosition(circle.ball.getPosition().x, circle.ball.getRadius());
                circle.speed.y *= -1;
            } else {
                circle.ball.move(0, circle.speed.y * dt.asSeconds());
            }
            if (circle.ball.getPosition().y + circle.speed.y * dt.asSeconds() > desktopMode.height - circle.ball.getRadius()) {
                circle.ball.setPosition(circle.ball.getPosition().x, desktopMode.height - circle.ball.getRadius());
                circle.speed.y *= -1;
            } else {
                circle.ball.move(0, circle.speed.y * dt.asSeconds());
            }
        }
    }
}

void Level::draw(sf::RenderWindow & window){
    for(int i = 0; i < greens.size(); i++){
        if (greens[i].exists){
            window.draw(greens[i].ball);
        }
    }

    for(int i = 0; i < reds.size(); i++){
        if (reds[i].exists){
            window.draw(reds[i].ball);
        }
    }
};