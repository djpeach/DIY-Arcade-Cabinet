#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>
#include <string>
#include <vector>
#include <queue>
#include "Duck.h"
#include "DEFINITIONS.h"

int main() {
    srand(time(0));

    enum class States {
      Game, GameOver, LeaderBoard
    };

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const float SCREEN_WIDTH = desktopMode.width;
    const float SCREEN_HEIGHT = desktopMode.height;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Duck Hunter", sf::Style::Fullscreen);

    sf::RectangleShape ground;
    ground.setSize(sf::Vector2f(SCREEN_WIDTH, GROUND_HEIGHT));
    ground.setFillColor(sf::Color(44, 186, 80));
    ground.setPosition(0, (SCREEN_HEIGHT - GROUND_HEIGHT));

    int score = 0;
    sf::Clock timer;
    int countdown = 60;
    sf::Text scoreText;
    sf::Text countdownText;

    sf::Font font;
    font.loadFromFile("Minecraft.ttf");
    scoreText.setFont(font);
    countdownText.setFont(font);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setCharacterSize(80);
    scoreText.setPosition(30, 15);
    countdownText.setFillColor(sf::Color::Black);
    countdownText.setString(std::to_string(countdown));
    countdownText.setCharacterSize(80);
    countdownText.setPosition(SCREEN_WIDTH - 60, 15);
    scoreText.setString(std::to_string(score));

    sf::Texture targetT;
    if (!targetT.loadFromFile("target.png")) {
        std::cout << "Error loading target texture" << std::endl;
        return -1;
    }

    sf::Texture duckT;
    if (!duckT.loadFromFile("duck.png")) {
        std::cout << "Error loading duck texture" << std::endl;
        return -1;
    }

    int directions[2] = {1, -1};

    bool w_down = false;
    bool a_down = false;
    bool s_down = false;
    bool d_down = false;

    bool gamePaused = false;

    States curState = States::Game;

    sf::Sprite target;
    target.setTexture(targetT);
    target.setOrigin(24, 24);
    target.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT - GROUND_HEIGHT) / 2);
    target.scale(3, 3);

    std::vector<djpeach::Duck> ducks(DUCK_COUNT);
    std::queue<int> duckQueue;

    for(int i=0;i<DUCK_COUNT;i++) {
      ducks[i].setTexture(duckT);
      duckQueue.push(i);
    }

    ducks[duckQueue.front()].flying = true;

    sf::Clock clock;

    while (window.isOpen()) {

      switch(curState) {
        case States::LeaderBoard: {
          break;
        }
        case States::Game: {
          if (timer.getElapsedTime().asSeconds() >= 1) {
            timer.restart();
            countdown--;
            countdownText.setString(std::to_string(countdown));
            if (countdown <= 0) {
              curState = States::GameOver;
            }
          }

          sf::Event event;
          while (window.pollEvent(event)) {

            switch (event.type) {

              case sf::Event::Closed:
                window.close();
                break;

              case sf::Event::KeyPressed:
                switch (event.key.code) {
                  case sf::Keyboard::Slash:
                    window.close();
                    break;
                  case sf::Keyboard::W:
                    w_down = true;
                    break;
                  case sf::Keyboard::A:
                    a_down = true;
                    break;
                  case sf::Keyboard::S:
                    s_down = true;
                    break;
                  case sf::Keyboard::D:
                    d_down = true;
                    break;
                  case sf::Keyboard::F:
                    for (int i=0;i<DUCK_COUNT;i++) {
                      sf::FloatRect duckBox = ducks[i].getGlobalBounds();
                      sf::FloatRect targetBox = target.getGlobalBounds();
                      if (targetBox.intersects(duckBox)) {
                        ducks[i].flying = false;
                        ducks[i].setPosition((rand() % (int)(SCREEN_WIDTH / 2)) + (SCREEN_WIDTH / 4), SCREEN_HEIGHT - GROUND_HEIGHT);
                        duckQueue.push(i);
                        ducks[i].setSpeed();
                        duckQueue.pop();
                        ducks[duckQueue.front()].flying = true;
                        score++;
                        scoreText.setString(std::to_string(score));
                        break;
                      }
                    }
                    int directions[2];
                    directions[0] = -1;
                    directions[0] = 1;
                    target.move(((rand() % 50) + 20) * directions[rand() % 2], -100);
                    break;
                  case sf::Keyboard::Z:
                    gamePaused = !gamePaused;
                    break;
                  default:
                    // std::cout << "Unknown key down" << std::endl;
                    break;
                }
                break;

                case sf::Event::KeyReleased:
                  switch (event.key.code) {
                    case sf::Keyboard::W:
                      w_down = false;
                      break;
                    case sf::Keyboard::A:
                      a_down = false;
                      break;
                    case sf::Keyboard::S:
                      s_down = false;
                      break;
                    case sf::Keyboard::D:
                      d_down = false;
                      break;
                    default:
                      // std::cout << "Unknown key up" << std::endl;
                      break;
                  }
                  break;

              default:
                // std::cout << "Unknown event" << std::endl;
                break;
            }
          }

          window.clear(sf::Color(181, 242, 255));

          sf::FloatRect targetBox = target.getGlobalBounds();

          if (!gamePaused) {
              if(w_down) { // move up
                if(target.getPosition().y - TARGET_SPEED > 0) {
                  target.move(0, -TARGET_SPEED);
                }
              }
              if(a_down) { // move left
                if(target.getPosition().x - TARGET_SPEED > 0) {
                  target.move(-TARGET_SPEED, 0);
                }
              }
              if(s_down) { // move down
                if(target.getPosition().y + TARGET_SPEED < SCREEN_HEIGHT - GROUND_HEIGHT) {
                  target.move(0, TARGET_SPEED);
                }
              }
              if(d_down) { // move right
                if(target.getPosition().x + TARGET_SPEED < SCREEN_WIDTH) {
                  target.move(TARGET_SPEED, 0);
                }
              }
          }

          window.draw(scoreText);
          window.draw(countdownText);

          for(int i=0;i<DUCK_COUNT;i++) {

            if (!gamePaused) {
              if (ducks[i].flying) {
                if (ducks[i].getPosition().y > (SCREEN_HEIGHT - GROUND_HEIGHT) * 0.75) {
              ducks[i].move(ducks[i].xSpeed * 2, ducks[i].ySpeed * 3);
                } else {
                          ducks[i].move(ducks[i].xSpeed, ducks[i].ySpeed);
                }
              }

              if (clock.getElapsedTime().asMilliseconds() > 1500 && !duckQueue.empty()) {
                clock.restart();
                duckQueue.pop();
                ducks[duckQueue.front()].flying = true;
              }

              if (ducks[i].getPosition().y < 0) {
                ducks[i].flying = false;
                ducks[i].setPosition((rand() % (int)(SCREEN_WIDTH / 2)) + (SCREEN_WIDTH / 4), SCREEN_HEIGHT - GROUND_HEIGHT);
                duckQueue.push(i);
              }
            }
            window.draw(ducks[i]);
          }



          window.draw(ground);
          window.draw(target);
          window.display();
          break;
        }
        case States::GameOver: {
          break;
        }
        default:
          break;
      }
    }
}
