#include <iostream>
#include <math.h>

#include "State_Game.hpp"
#include "Game.hpp"

State_Game::State_Game(SharedContext & ctx) : State_Base(ctx),
curPlayer(0), player1Index(63), player2Index(0) {
  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);
  for (int i=0; i<64; i++) {
    sf::Vector2f tilePosition(tileSize.x * (i % 8), tileSize.y * floor(i / 8));
    unsigned int whiteHue = (i / 8) % 2 == 0 ? 115 + (100 * (i % 2)) : 115 + (100 * !(i % 2));
    sf::Color tileColor = sf::Color(whiteHue, whiteHue, whiteHue);
    Tile tile(tileSize, tilePosition, tileColor);
    board.push_back(tile);
    if (i == 0) {
      tile.setColor(sf::Color(50, 50, 50, 100));
      player1Tile = tile;
    } else if (i == 63) {
      tile.setColor(sf::Color(200, 15, 15, 120));
      player2Tile = tile;
    }
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
          player1Index = player1Index - 8 >= 0 ? player1Index - 8 : player1Index + 56;
          break;
        case sf::Keyboard::S:
          player1Index = player1Index + 8 <= 63 ? player1Index + 8 : player1Index - 56;
          break;
        case sf::Keyboard::A:
          player1Index = player1Index % 8 == 0 ? player1Index + 7 : player1Index - 1;
          break;
        case sf::Keyboard::D:
          player1Index = (player1Index + 1) % 8 == 0 ? player1Index - 7 : player1Index + 1;
          break;
        case sf::Keyboard::F:
          curPlayer = !curPlayer;
        default:
          break;
      }
    } else if (curPlayer == 1) {
      switch (e.key.code) {
        case sf::Keyboard::I:
          player2Index = player2Index - 8 >= 0 ? player2Index - 8 : player2Index + 56;
          break;
        case sf::Keyboard::K:
          player2Index = player2Index + 8 <= 63 ? player2Index + 8 : player2Index - 56;
          break;
        case sf::Keyboard::J:
          player2Index = player2Index % 8 == 0 ? player2Index + 7 : player2Index - 1;
          break;
        case sf::Keyboard::L:
          player2Index = (player2Index + 1) % 8 == 0 ? player2Index - 7 : player2Index + 1;
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
  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);

  player1Tile.setPosition(sf::Vector2f(tileSize.x * (player1Index % 8), tileSize.y * floor(player1Index / 8)));
  player2Tile.setPosition(sf::Vector2f(tileSize.x * (player2Index % 8), tileSize.y * floor(player2Index / 8)));
}

void State_Game::render() {
  for (auto & tile : board) {
    ctx.window.draw(tile);
  }
  ctx.window.draw(player1Tile);
  ctx.window.draw(player2Tile);
}
