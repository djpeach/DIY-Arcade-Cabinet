#pragma once

#include <SFML/Graphics.hpp>

namespace djpeach {

  class Duck : public sf::Sprite {
  public:
    Duck();
    void setSpeed();
    float xSpeed;
    float ySpeed;
    bool flying;
  };

}
