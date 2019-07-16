#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include <SFML/Graphics.hpp>

// MAC
// #define ENEMY_WIDTH 100
// #define ENEMY_HEIGHT 200
// #define PADDLE_WIDTH 250
// #define PADDLE_HEIGHT 100
// #define LIFE_SIDE_LENGTH 75
// #define POINTS_SIDE_LENGTH 100

// PI
#define ENEMY_WIDTH 50
#define ENEMY_HEIGHT 100
#define PADDLE_WIDTH 125
#define PADDLE_HEIGHT 50
#define LIFE_SIDE_LENGTH 35
#define POINTS_SIDE_LENGTH 50

int main() {

    std::srand((uint)time(nullptr));

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
    sf::Vector2u windowSize = window.getSize();

    sf::RectangleShape paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    paddle.setFillColor(sf::Color(0, 255, 0, 255));
    sf::Vector2f paddleSize = paddle.getSize();
    paddle.setOrigin(paddleSize.x / 2, paddleSize.y);
    paddle.setPosition(windowSize.x / 2, windowSize.y);

    int paddleSpeed;
    int paddleInitSpeed = 5;
    int paddleBoostSpeed = 10;

    int hmBlocks = 7;
    int hmLives = 3;
    std::vector<sf::RectangleShape> blocks(hmBlocks);
    float blockSpeeds[hmBlocks];
    float speedMulitplier = 1;

    int score = 0;
    std::vector<sf::RectangleShape> lives(hmLives);
    bool extraLifeOnScreen = false;
    bool gameOver = false;

    int levelUpAmount = 50;
    int levelUpAmountIncrement = 25;

    float enemyBuffer = windowSize.y / hmBlocks;

    for(int i=0;i<hmLives;i++) {
        sf::RectangleShape rect(sf::Vector2f(LIFE_SIDE_LENGTH, LIFE_SIDE_LENGTH));
        rect.setFillColor(sf::Color(255, 0, 0, 255));
        sf::Vector2f rectSize = rect.getSize();
        rect.setOrigin(rectSize.x, 0);
        rect.setPosition(windowSize.x - ((LIFE_SIDE_LENGTH + 25) * i + 25), 25);
        lives[i] = rect;
    }

    for(int i=0;i<hmBlocks;i++) {
        sf::RectangleShape rect(sf::Vector2f(ENEMY_WIDTH, ENEMY_HEIGHT));
        rect.setPosition(std::rand() % (windowSize.x - ENEMY_WIDTH), 0 - (i * enemyBuffer));
        blocks[i] = rect;
        blockSpeeds[i] = (std::rand() % 3) + 2;
    }

    std::map<int, bool> pressedKeys;

    sf::Font font;
    if (!font.loadFromFile("Minecraft.ttf")) {
        std::cout << "Could not load font" << std::endl;
        return 1;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score));
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setCharacterSize(80);
    scoreText.setPosition(25, 25);

    sf::Text gameOverText;
    sf::Text gameOverScore;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(200);
    sf::FloatRect gameOverTextBounds = gameOverText.getGlobalBounds();
    gameOverText.setOrigin(gameOverTextBounds.width / 2, gameOverTextBounds.height / 2);
    gameOverText.setPosition(windowSize.x / 2, (windowSize.y / 2) - 200);
    gameOverScore.setFont(font);
    gameOverScore.setCharacterSize(150);
    gameOverScore.setString("000");
    gameOverScore.setFillColor(sf::Color::Yellow);
    sf::FloatRect gameOverScoreBounds = gameOverScore.getGlobalBounds();
    gameOverScore.setOrigin(gameOverScoreBounds.width / 2, gameOverScoreBounds.height / 2);
    gameOverScore.setPosition(windowSize.x / 2, (windowSize.y / 2) + 200);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Num1) {
                      score = 0;
                      hmLives = 3;
                      gameOver = false;
                      for (int i=0;i<hmBlocks;i++) {
                        blocks[i].setSize(sf::Vector2f(ENEMY_WIDTH, ENEMY_HEIGHT));
                        blocks[i].setFillColor(sf::Color(255, 255, 255, 255));
                        sf::Vector2f blockPos = blocks[i].getPosition();
                        blocks[i].setPosition(blockPos.x, blockPos.y - windowSize.y);
                      }
                    }
                    pressedKeys[event.key.code] = true;
                    break;
                case sf::Event::KeyReleased:
                    pressedKeys[event.key.code] = false;
                    break;
                default:
                    break;
            }
        }

        if (!gameOver) {
            sf::Vector2f paddlePos = paddle.getPosition();
            if (!(pressedKeys[sf::Keyboard::D] && pressedKeys[sf::Keyboard::A])) {
                if (pressedKeys[sf::Keyboard::F]) {
                    paddleSpeed = paddleBoostSpeed;
                } else {
                    paddleSpeed = paddleInitSpeed;
                }
                if (pressedKeys[sf::Keyboard::D]) {
                    paddle.setPosition(paddlePos.x + paddleSpeed, paddlePos.y);
                }
                if (pressedKeys[sf::Keyboard::A]) {
                    paddle.setPosition(paddlePos.x - paddleSpeed, paddlePos.y);
                }
            }

            paddlePos = paddle.getPosition();
            if (paddlePos.x - (paddleSize.x / 2) < 0) {
                paddle.setPosition(paddleSize.x / 2, paddlePos.y);
            } else if (paddlePos.x + (paddleSize.x / 2) > windowSize.x) {
                paddle.setPosition(windowSize.x - (paddleSize.x / 2), paddlePos.y);
            }

            for (int i=0;i<hmBlocks;i++) {
                if (blocks[i].getGlobalBounds().intersects(paddle.getGlobalBounds())) {
                    sf::Vector2f blockPos = blocks[i].getPosition();
                    if (blocks[i].getSize().x == LIFE_SIDE_LENGTH) {
                        if (hmLives < 3) {
                            hmLives++;
                            blocks[i].setPosition(std::rand() % (int)(windowSize.x - blocks[i].getSize().x), blockPos.y - (windowSize.y * 2));
                        }
                    } else if (blocks[i].getSize().y == POINTS_SIDE_LENGTH) {
                        score += 25;
                        blocks[i].setPosition(std::rand() % (int)(windowSize.x - blocks[i].getSize().x), blockPos.y - (windowSize.y * 2));
                    } else {
                        if (hmLives > 0) {
                            hmLives--;
                            blocks[i].setPosition(std::rand() % (int)(windowSize.x - blocks[i].getSize().x), blockPos.y - (windowSize.y * 2));
                        } else {
                            gameOver = true;
                        }
                    }

                }
                sf::Vector2f blockPos = blocks[i].getPosition();
                float newY, newX;
                if (blockPos.y > windowSize.y) {
                    if (blocks[i].getSize().x < 100) {
                        extraLifeOnScreen = false;
                    }
                    int extraLifeChance = std::rand() % 10;
                    int bonusPointsChance = std::rand() % 15;
                    if (extraLifeChance == 0 && !extraLifeOnScreen) {
                        blocks[i].setSize(sf::Vector2f(LIFE_SIDE_LENGTH, LIFE_SIDE_LENGTH));
                        blocks[i].setFillColor(sf::Color(255, 0, 0, 255));
                        extraLifeOnScreen = true;
                    } else if (bonusPointsChance == 0) {
                        blocks[i].setSize(sf::Vector2f(POINTS_SIDE_LENGTH, POINTS_SIDE_LENGTH));
                        blocks[i].setFillColor(sf::Color::Blue);
                    } else {
                        blocks[i].setSize(sf::Vector2f(ENEMY_WIDTH, ENEMY_HEIGHT));
                        blocks[i].setFillColor(sf::Color(255, 255, 255, 255));
                    }
                    score++;
                    if (score > 0 && score % levelUpAmount == 0 && speedMulitplier < 3) {
                        speedMulitplier += 0.3f;
                        levelUpAmount += levelUpAmountIncrement;
                        levelUpAmountIncrement += 25;
                    }
                    blockSpeeds[i] = ((std::rand() % 3) + 2) * speedMulitplier;
                    newY = 0 - enemyBuffer;
                    newX = std::rand() % (int)(windowSize.x - blocks[i].getSize().x);
                } else {
                    newY = blockPos.y + blockSpeeds[i];
                    newX = blockPos.x;
                }
                blocks[i].setPosition(newX, newY);
            }

            scoreText.setString(std::to_string(score));
        }

        window.clear();

        if (!gameOver) {
            window.draw(paddle);
            for (int i=0;i<hmBlocks;i++) {
                window.draw(blocks[i]);
            }
            for (int i=0;i<hmLives;i++) {
                window.draw(lives[i]);
            }
            window.draw(scoreText);
        } else {
            gameOverScore.setString(std::to_string(score));
            window.draw(gameOverText);
            window.draw(gameOverScore);
        }

        window.display();

    }

    return 0;
}
