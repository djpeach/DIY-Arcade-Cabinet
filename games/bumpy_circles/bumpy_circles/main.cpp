#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include<time.h> 

#include "Level.hpp"

int main() {

    sf::Time dt;
    sf::Clock speedClock;
    sf::Clock gameClock;
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    const float SCREEN_W = desktopMode.width;
    const float SCREEN_H = desktopMode.height;

    bool upPressed = false;
    bool dnPressed = false;
    bool rtPressed = false;
    bool lfPressed = false;

    float screenX = SCREEN_W/2;
    float screenY = SCREEN_H/2;

    const int numberLevels = 3;

    // Level(maxTime, numberGreen, numberRed, greenMaxSpeed, redMaxSpeed)
    Level levels[3] = {Level(60, 1, 1, 50, 150), Level(60, 2, 2, 75, 190), Level(60, 3, 3, 100, 215)};

    srand(time(0));

    int USER_RADIUS = 50;
    int USER_SPEED = 1000; // px/s
    float FPS = (float)(1.0/120);
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Bumpy Circles", sf::Style::Fullscreen);

    sf::CircleShape circle(USER_RADIUS);
    int curLvl = 0;

    circle.setFillColor(sf::Color(66,135,245));
    circle.setOrigin(50,50);

    circle.setPosition(SCREEN_W/2, SCREEN_H/2);

    while (window.isOpen()) {
      dt += gameClock.restart();
        sf::Event event;

        while (window.pollEvent(event)) {

          switch (event.type) {

            case sf::Event::Closed:
              window.close();
              break;

            case sf::Event::KeyPressed: {
              switch (event.key.code){
                case sf::Keyboard::Slash:
                  window.close();
                  break;

                case sf::Keyboard::W:
                  upPressed = true;
                  break;

                case sf::Keyboard::S:
                  dnPressed = true;
                  break;

                case sf::Keyboard::A:
                  lfPressed = true;
                  break;

                case sf::Keyboard::D:
                  rtPressed = true;
                  break;
                default:
                  break;
              }
              break;
            }
            case sf::Event::KeyReleased: {
              switch (event.key.code){
                case sf::Keyboard::W:
                  upPressed = false;
                  break;

                case sf::Keyboard::S:
                  dnPressed = false;
                  break;

                case sf::Keyboard::A:
                  lfPressed = false;
                  break;

                case sf::Keyboard::D:
                  rtPressed = false;
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

        if (dt.asSeconds() > FPS) {
          if (upPressed){
            if (screenY - (USER_SPEED * dt.asSeconds()) > circle.getRadius()){
              circle.move(0,-USER_SPEED * dt.asSeconds());
              screenY -= USER_SPEED * dt.asSeconds();
            }
          }
          if (dnPressed){
            if ((screenY + circle.getRadius()) + (USER_SPEED * dt.asSeconds()) < SCREEN_H){
              circle.move(0,USER_SPEED * dt.asSeconds());
              screenY += USER_SPEED * dt.asSeconds();
            }
          }
          if (rtPressed){
            if ((screenX + circle.getRadius()) + (USER_SPEED * dt.asSeconds()) < SCREEN_W){
              circle.move(USER_SPEED * dt.asSeconds(),0);
              screenX += USER_SPEED * dt.asSeconds();
            }
          }
          if (lfPressed){
            if (screenX - (USER_SPEED * dt.asSeconds()) > circle.getRadius()){
              circle.move(-USER_SPEED * dt.asSeconds(),0);
              screenX -= USER_SPEED * dt.asSeconds();
            }
          }
            dt -= sf::seconds(FPS);
        }

        window.clear();

        sf::Vector2f circlePos = circle.getPosition();
        levels[curLvl].handleCollisions();
        levels[curLvl].registerCollisions(circlePos, USER_RADIUS);

        levels[curLvl].update(dt);

        window.draw(circle);

        levels[curLvl].draw(window);
        
        if (levels[curLvl].cleared && curLvl + 1 < numberLevels) {
          curLvl++;
        } 
        if (curLvl + 1 == numberLevels && levels[curLvl].cleared) {
          exit(1);
        }

        window.display();

    }
}
