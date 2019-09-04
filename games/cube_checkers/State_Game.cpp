#include <iostream>
#include <math.h>

#include "State_Game.hpp"
#include "Game.hpp"

State_Game::State_Game(SharedContext & ctx) : State_Base(ctx),
curPlayer(0), player1Tile(63), player2Tile(0) {
  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);
  for (int i=0; i<64; i++) {
    sf::Vector2f tilePosition(tileSize.x * (i % 8), tileSize.y * floor(i / 8));
    unsigned int whiteHue = (i / 8) % 2 == 0 ? 115 + (100 * (i % 2)) : 115 + (100 * !(i % 2));
    sf::Color tileColor = sf::Color(whiteHue, whiteHue, whiteHue);
    Tile tile(tileSize, tilePosition, tileColor);
    board.push_back(tile);
  }
}

State_Game::~State_Game() {}

void State_Game::handleEvent(sf::Event e) {
  if (e.type == sf::Event::Closed) {
    ctx.window.close();
  } else if (e.type == sf::Event::KeyPressed) {
    switch (e.key.code) {
      case sf::Keyboard::Slash:
        ctx.window.close();
        break;
      default:
        break;
    }
    if (curPlayer == 0) {
      switch (e.key.code) {
        case sf::Keyboard::W:
          player1Tile = player1Tile - 8 >= 0 ? player1Tile - 8 : player1Tile + 56;
          break;
        case sf::Keyboard::S:
          player1Tile = player1Tile + 8 <= 63 ? player1Tile + 8 : player1Tile - 56;
          break;
        case sf::Keyboard::A:
          player1Tile = player1Tile % 8 == 0 ? player1Tile + 7 : player1Tile - 1;
          break;
        case sf::Keyboard::D:
          player1Tile = (player1Tile + 1) % 8 == 0 ? player1Tile - 7 : player1Tile + 1;
          break;
        case sf::Keyboard::F:
          curPlayer = !curPlayer;
        default:
          break;
      }
    } else if (curPlayer == 1) {
      switch (e.key.code) {
        case sf::Keyboard::I:
          player2Tile = player2Tile - 8 >= 0 ? player2Tile - 8 : player2Tile + 56;
          break;
        case sf::Keyboard::K:
          player2Tile = player2Tile + 8 <= 63 ? player2Tile + 8 : player2Tile - 56;
          break;
        case sf::Keyboard::J:
          player2Tile = player2Tile % 8 == 0 ? player2Tile + 7 : player2Tile - 1;
          break;
        case sf::Keyboard::L:
          player2Tile = (player2Tile + 1) % 8 == 0 ? player2Tile - 7 : player2Tile + 1;
          break;
        case sf::Keyboard::H:
          curPlayer = !curPlayer;
        default:
          break;
      }
    }
  }
}

void State_Game::update() {
  if (curPlayer == 0) {
    for(int i=0; i<64; i++) {
      if (i == player1Tile) {
        board[i].setColor(sf::Color(250, 250, 150));
      } else {
        unsigned int whiteHue = (i / 8) % 2 == 0 ? 115 + (100 * (i % 2)) : 115 + (100 * !(i % 2));
        board[i].setColor(sf::Color(whiteHue, whiteHue, whiteHue));
      }
    }
  } else if (curPlayer == 1) {
    for(int i=0; i<64; i++) {
      if (i == player2Tile) {
        board[i].setColor(sf::Color(250, 250, 150));
      } else {
        unsigned int whiteHue = (i / 8) % 2 == 0 ? 115 + (100 * (i % 2)) : 115 + (100 * !(i % 2));
        board[i].setColor(sf::Color(whiteHue, whiteHue, whiteHue));
      }
    }
  }
}

void State_Game::render() {
  for (auto & tile : board) {
    ctx.window.draw(tile);
  }
}
