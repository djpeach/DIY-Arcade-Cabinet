#include "Duck.h"
#include "DEFINITIONS.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

namespace djpeach {

  Duck::Duck() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const float SCREEN_WIDTH = desktopMode.width;
    const float SCREEN_HEIGHT = desktopMode.height;

    static bool seeded = false;
    if(!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    this->setOrigin(16, 0);
    this->setScale(3, 3);
    this->setPosition((rand() % (int)(SCREEN_WIDTH / 2)) + (SCREEN_WIDTH / 4), SCREEN_HEIGHT - GROUND_HEIGHT);

    this->xSpeed = this->getPosition().x < SCREEN_WIDTH / 2 ? DUCK_SPEED : -DUCK_SPEED;
    if(this->xSpeed < 0) {
      this->scale(-1.f, 1.f);
    }
    this->ySpeed = -1 * DUCK_SPEED;
    this->flying = false;
  }

  void Duck::setSpeed() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const float SCREEN_WIDTH = desktopMode.width;
    const float SCREEN_HEIGHT = desktopMode.height;
    this->setScale(3, 3);
    this->xSpeed = this->getPosition().x < SCREEN_WIDTH / 2 ? DUCK_SPEED : -DUCK_SPEED;
    if(this->xSpeed < 0) {
      this->scale(-1.f, 1.f);
    }
    this->ySpeed = -1 * DUCK_SPEED;
  }

}
