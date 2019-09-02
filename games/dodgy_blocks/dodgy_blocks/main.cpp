#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sqlite3.h>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// MAC
// #define ENEMY_WIDTH 100
// #define ENEMY_HEIGHT 200
// #define PADDLE_WIDTH 250
// #define PADDLE_HEIGHT 100
// #define LIFE_SIDE_LENGTH 75
// #define POINTS_SIDE_LENGTH 100
// #define MIN_SPEED 2
// #define MAX_SPEED 5
// #define PADDLE_SPEED 5
// #define PADDLE_BOOST_SPEED 10

// PI
#define ENEMY_WIDTH 50
#define ENEMY_HEIGHT 100
#define PADDLE_WIDTH 125
#define PADDLE_HEIGHT 50
#define LIFE_SIDE_LENGTH 35
#define POINTS_SIDE_LENGTH 50
#define MIN_SPEED 1
#define MAX_SPEED 4
#define PADDLE_SPEED 2
#define PADDLE_BOOST_SPEED 5

std::string scoreStrings[10];
int curStoreString = 0;

// Create a callback function
int scoreStringsCallback(void *NotUsed, int argc, char **argv, char **azColName) {

  for (int i=0;i<argc;i++) {
    if (strcmp(azColName[i], "NAME") == 0) {
      scoreStrings[curStoreString] = argv[i];
      scoreStrings[curStoreString] += ": ";
    } else if (strcmp(azColName[i], "SCORE") == 0) {
      scoreStrings[curStoreString] += argv[i];
      curStoreString++;
    }
  }

  return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {

  std::cout << argc << std::endl;

  return 0;
}

int main() {

    sf::Music music;


    sf::SoundBuffer extraPointsSoundBuffer;
    sf::SoundBuffer extraLifeSoundBuffer;
    sf::SoundBuffer lostALifeSoundBuffer;

    if(!extraPointsSoundBuffer.loadFromFile("extraPoints.wav") ||
      !extraLifeSoundBuffer.loadFromFile("extraLife.wav") ||
      !lostALifeSoundBuffer.loadFromFile("lostALife.wav") ||
      !music.openFromFile("music.wav")
    ) {
      std::cout << "Could not load a sound from file" << std::endl;
      return -1;
    }

    music.setLoop(true);
    music.setVolume(40.f);
    music.play();

    sf::Sound extraPointsSound;
    sf::Sound extraLifeSound;
    sf::Sound lostALifeSound;

    extraPointsSound.setBuffer(extraPointsSoundBuffer);
    extraLifeSound.setBuffer(extraLifeSoundBuffer);
    lostALifeSound.setBuffer(lostALifeSoundBuffer);

    sqlite3 *db;
    char * errMsgTable = 0;
    int rc;
    std::string sql;
    rc = sqlite3_open("dodgy_blocks.db", &db);

    if (rc) {
      std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_close(db);
      return (1);
    }
    sql = "CREATE TABLE IF NOT EXISTS HIGHSCORES ("
          "ID INTEGER PRIMARY KEY     AUTOINCREMENT,"
          "NAME           TEXT    NOT NULL,"
          "SCORE          INTEGER     NOT NULL);";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsgTable);
    sqlite3_close(db);

    std::srand((uint)time(nullptr));

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
    sf::Vector2u windowSize = window.getSize();

    sf::RectangleShape paddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    paddle.setFillColor(sf::Color(0, 255, 0, 255));
    sf::Vector2f paddleSize = paddle.getSize();
    paddle.setOrigin(paddleSize.x / 2, paddleSize.y);
    paddle.setPosition(windowSize.x / 2, windowSize.y);

    int paddleSpeed;
    int paddleInitSpeed = PADDLE_SPEED;
    int paddleBoostSpeed = PADDLE_BOOST_SPEED;

    int hmBlocks = 4;
    int hmLives = 3;
    std::vector<sf::RectangleShape> blocks(hmBlocks);
    float blockSpeeds[hmBlocks];
    float speedMulitplier = 1;

    int score = 0;
    std::vector<sf::RectangleShape> lives(hmLives);
    bool extraLifeOnScreen = false;
    bool gameOver = false;
    bool showingGameOver = true;
    bool scoresSaved = false;

    int levelUpAmount = 50;
    int levelUpAmountIncrement = 25;
    sf::Text highscores[10];

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
        blockSpeeds[i] = (std::rand() % (MAX_SPEED - MIN_SPEED)) + MIN_SPEED;
    }

    std::map<int, bool> pressedKeys;

    sf::Font font;
    if (!font.loadFromFile("Minecraft.ttf")) {
        std::cout << "Could not load font" << std::endl;
        return 1;
    }

    for (int i=0;i<10;++i) {
      sf::Text score;
      if (i == 0) {
        score.setFillColor(sf::Color::Green);
      } else if (i == 1) {
        score.setFillColor(sf::Color::Cyan);
      } else if (i == 2) {
        score.setFillColor(sf::Color::Yellow);
      } else {
        score.setFillColor(sf::Color::White);
      }
      score.setFont(font);
      score.setCharacterSize(70);
      score.setString("AAA: 22788");
      if (i < 5) {
        score.setPosition(50, (((windowSize.y - 50) / 11) * (i + 1)) + (i * 25));
      } else {
        score.setPosition(((windowSize.x - 50) / 2), (((windowSize.y - 50) / 11) * ((i - 5) + 1)) + ((i - 5) * 25));
      }
      highscores[i] = score;
    }

    std::string letters[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    int curLetterIndex = 0;
    std::string name = "";

    sf::Text nameText;
    nameText.setFont(font);
    nameText.setString("AAA");
    nameText.setFillColor(sf::Color::Yellow);
    nameText.setCharacterSize(80);
    sf::FloatRect nameTextBounds = nameText.getGlobalBounds();
    nameText.setOrigin(nameTextBounds.width / 2, nameTextBounds.height / 2);
    nameText.setPosition(windowSize.x / 2, (windowSize.y / 2) - 400);
    nameText.setString(name);

    sf::Text gameOverInstructionText;
    gameOverInstructionText.setFont(font);
    gameOverInstructionText.setString("Press P1 Red to submit score");
    gameOverInstructionText.setFillColor(sf::Color::White);
    gameOverInstructionText.setCharacterSize(70);
    sf::FloatRect gameOverInstructionTextBounds = gameOverInstructionText.getGlobalBounds();
    gameOverInstructionText.setOrigin(gameOverInstructionTextBounds.width / 2, gameOverInstructionTextBounds.height / 2);
    gameOverInstructionText.setPosition(windowSize.x / 2, windowSize.y / 2);

    sf::Text letterText;
    letterText.setFont(font);
    letterText.setString("A");
    letterText.setFillColor(sf::Color::Cyan);
    letterText.setCharacterSize(120);
    sf::FloatRect letterTextBounds = letterText.getGlobalBounds();
    letterText.setOrigin(letterTextBounds.width / 2, letterTextBounds.height / 2);
    letterText.setPosition(windowSize.x / 2, windowSize.y / 2);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score));
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setCharacterSize(80);
    scoreText.setPosition(25, 25);

    sf::Text getNameText;
    bool gettingName = false;
    bool showingScores = false;
    sf::Text gameOverText;
    sf::Text gameOverScore;
    gameOverText.setFont(font);
    getNameText.setFont(font);
    gameOverText.setString("Game Over");
    getNameText.setString("Use up & down to enter your name,\n      press P1 Red to select letter");
    gameOverText.setCharacterSize(200);
    getNameText.setCharacterSize(70);
    sf::FloatRect gameOverTextBounds = gameOverText.getGlobalBounds();
    gameOverText.setOrigin(gameOverTextBounds.width / 2, gameOverTextBounds.height / 2);
    gameOverText.setPosition(windowSize.x / 2, (windowSize.y / 2) - 200);
    sf::FloatRect getNameTextBounds = getNameText.getGlobalBounds();
    getNameText.setOrigin(getNameTextBounds.width / 2, getNameTextBounds.height / 2);
    getNameText.setPosition(windowSize.x / 2, (windowSize.y / 2) - 200);
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
                    if (gameOver && showingGameOver) {
                      if (event.key.code == sf::Keyboard::F) {
                        showingGameOver = false;
                        gettingName = true;
                      }
                    } else if (gettingName) {
                      if (name.length() < 3) {
                        if (event.key.code == sf::Keyboard::W) {
                          if (curLetterIndex == 25) {
                            curLetterIndex = 0;
                          } else {
                            curLetterIndex++;
                          }
                        }
                        if (event.key.code == sf::Keyboard::S) {
                          if (curLetterIndex == 0) {
                            curLetterIndex = 25;
                          } else {
                            curLetterIndex--;
                          }
                        }
                        if (event.key.code == sf::Keyboard::F) {
                          name += letters[curLetterIndex];
                          curLetterIndex = 0;
                        }
                        letterText.setString(letters[curLetterIndex]);
                        nameText.setString(name);
                      } else {
                        if (event.key.code == sf::Keyboard::F) {
                          gettingName = false;
                          showingScores = true;
                        }
                      }
                    }
                    if (event.key.code == sf::Keyboard::Slash) {
                      window.close();
                    }
                    if (scoresSaved && event.key.code == sf::Keyboard::Num1) {
                      score = 0;
                      hmLives = 3;
                      gameOver = false;
                      speedMulitplier = 1;
                      levelUpAmount = 50;
                      levelUpAmountIncrement = 25;
                      for (int i=0;i<hmBlocks;i++) {
                        blocks[i].setSize(sf::Vector2f(ENEMY_WIDTH, ENEMY_HEIGHT));
                        blocks[i].setFillColor(sf::Color(255, 255, 255, 255));
                        sf::Vector2f blockPos = blocks[i].getPosition();
                        blocks[i].setPosition(blockPos.x, blockPos.y - windowSize.y);
                      }
                      extraLifeOnScreen = false;
                      gameOver = false;
                      showingGameOver = true;
                      scoresSaved = false;
                      gettingName = false;
                      showingScores = false;
                      name = "";
                      nameText.setString(name);
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
                            extraLifeSound.play();
                            hmLives++;
                            blocks[i].setPosition(std::rand() % (int)(windowSize.x - blocks[i].getSize().x), blockPos.y - (windowSize.y * 2));
                        } else {
                          extraPointsSound.play();
                          score += 10;
                          blocks[i].setPosition(std::rand() % (int)(windowSize.x - blocks[i].getSize().x), blockPos.y + 100);
                        }
                    } else if (blocks[i].getSize().y == POINTS_SIDE_LENGTH) {
                        extraPointsSound.play();
                        score += 25;
                        blocks[i].setPosition(std::rand() % (int)(windowSize.x - blocks[i].getSize().x), blockPos.y - (windowSize.y * 2));
                    } else {
                        if (hmLives > 0) {
                            lostALifeSound.play();
                            hmLives--;
                            blocks[i].setPosition(std::rand() % (int)(windowSize.x - blocks[i].getSize().x), blockPos.y - (windowSize.y * 2));
                        } else {
                            lostALifeSound.play();
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
                    if (score > 0 && score % levelUpAmount == 0) {
                        speedMulitplier += 0.4f;
                        levelUpAmount += levelUpAmountIncrement;
                        levelUpAmountIncrement += 25;
                    }
                    blockSpeeds[i] = (std::rand() % (MAX_SPEED - MIN_SPEED)) + MIN_SPEED * speedMulitplier;
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

        if (showingScores && !scoresSaved) {
          sqlite3 *db;
          char * errMsg = 0;
          int rcStore;
          std::string sql;
          rcStore = sqlite3_open("dodgy_blocks.db", &db);

          if (rcStore) {
            std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return (1);
          }
          sql = "INSERT INTO HIGHSCORES ('NAME', 'SCORE') VALUES ('" + name + "', " + std::to_string(score) + ");";
          rcStore = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
          int rcGet;
          errMsg = 0;
          rcGet = sqlite3_open("dodgy_blocks.db", &db);

          if (rcGet) {
            std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return (1);
          }
          sql = "SELECT NAME, SCORE FROM 'HIGHSCORES' ORDER BY SCORE DESC LIMIT 10;";
          rcGet = sqlite3_exec(db, sql.c_str(), scoreStringsCallback, 0, &errMsg);
          sqlite3_close(db);
          curStoreString = 0;
          scoresSaved = true;
        }

        window.clear();

        if (gameOver && showingGameOver) {
          gameOverScore.setString(std::to_string(score));
          window.draw(gameOverText);
          window.draw(gameOverScore);
          window.draw(gameOverInstructionText);
        } else if (gettingName) {
            window.draw(getNameText);
            window.draw(nameText);
            window.draw(letterText);
        } else if (showingScores) {
          for(int i=0;i<10;i++) {
            highscores[i].setString(scoreStrings[i]);
            window.draw(highscores[i]);
          }
        } else {
          window.draw(paddle);
          for (int i=0;i<hmBlocks;i++) {
              window.draw(blocks[i]);
          }
          for (int i=0;i<hmLives;i++) {
              window.draw(lives[i]);
          }
          window.draw(scoreText);
        }

        window.display();

    }

    return 0;
}
