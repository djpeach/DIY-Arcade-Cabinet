#include <iostream>
#include <math.h>

#include "State_Game.hpp"
#include "Game.hpp"
#include "Cube.hpp"

State_Game::State_Game(SharedContext & ctx) : State_Base(ctx),
player1(), player2() {

  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);

  for (int i=0; i<64; i++) {
    sf::Vector2f tilePosition(tileSize.x * (i % 8), tileSize.y * floor(i / 8));
    unsigned int whiteHue = (i / 8) % 2 != 0 ? 115 + (100 * (i % 2)) : 115 + (100 * !(i % 2));
    if (whiteHue == 115) {
      if ((i / 8) < 3) {
        Cube cube = Cube(tileSize * 0.8f, sf::Vector2f(tilePosition.x + tileSize.x / 2, tilePosition.y + tileSize.y / 2), sf::Color(200, 15, 15));
        player1.addCube(cube);
      } else if ((i / 8) > 4) {
        Cube cube = Cube(tileSize * 0.8f, sf::Vector2f(tilePosition.x + tileSize.x / 2, tilePosition.y + tileSize.y / 2), sf::Color(20, 20, 20));
        player2.addCube(cube);
      }
    }
    sf::Color tileColor = sf::Color(whiteHue, whiteHue, whiteHue);
    Tile tile(tileSize, tilePosition, tileColor);
    tile.index = i;
    board.push_back(tile);

    if (i == 0) {
      tile.setColor(sf::Color(200, 15, 15, 120));
      player1.setTile(tile);
    } else if (i == 63) {
      tile.setColor(sf::Color(50, 50, 50, 100));
      player2.setTile(tile);
    }

  }

  player1.index = 1;
  player2.index = 62;
  player1.isTurn = true;
  player1.name = "Player 1";
  player2.name = "Player 2";
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

    if (player1.isTurn) {
      switch (e.key.code) {
        case sf::Keyboard::W:
          player1.index = player1.index - 8 >= 0 ? player1.index - 8 : player1.index + 56;
          break;
        case sf::Keyboard::S:
          player1.index = player1.index + 8 <= 63 ? player1.index + 8 : player1.index - 56;
          break;
        case sf::Keyboard::A:
          player1.index = player1.index % 8 == 0 ? player1.index + 7 : player1.index - 1;
          break;
        case sf::Keyboard::D:
          player1.index = (player1.index + 1) % 8 == 0 ? player1.index - 7 : player1.index + 1;
          break;
        case sf::Keyboard::F:
          selectPiece();
        default:
          break;
      }
    } else if (player2.isTurn) {
      switch (e.key.code) {
        case sf::Keyboard::I:
          player2.index = player2.index - 8 >= 0 ? player2.index - 8 : player2.index + 56;
          break;
        case sf::Keyboard::K:
          player2.index = player2.index + 8 <= 63 ? player2.index + 8 : player2.index - 56;
          break;
        case sf::Keyboard::J:
          player2.index = player2.index % 8 == 0 ? player2.index + 7 : player2.index - 1;
          break;
        case sf::Keyboard::L:
          player2.index = (player2.index + 1) % 8 == 0 ? player2.index - 7 : player2.index + 1;
          break;
        case sf::Keyboard::H:
          player2.isTurn = false;
          player1.isTurn = true;
        default:
          break;
      }
    }
  }
}

void State_Game::selectPiece() {
  Player & currentPlayer = player1.isTurn ? player1 : player2;
  Player & otherPlayer = player1.isTurn ? player2 : player1;
  Cube * pieceOnSelectedTile;

  if (currentPlayer.getPieceOnTile(currentPlayer.curTile)) {
    currentPlayer.selectPiece();
    calcAllowedTiles(currentPlayer, otherPlayer);
  }
}

Tile State_Game::getTileAtIndex(int i) {
  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);
  sf::Vector2f tilePosition(tileSize.x * (i % 8), tileSize.y * floor(i / 8));
  Tile tile(tileSize, tilePosition, sf::Color(15, 200, 15, 100));
  tile.index = i;
  return tile;
}

void State_Game::calcAllowedTiles(Player & currentPlayer, Player & otherPlayer) {
  allowedTiles.clear();
  int initIndex = currentPlayer.index;
  Cube * pieceOnSelectedTile;
  int selectedPieceValue = currentPlayer.getPieceOnTile(currentPlayer.curTile)->value;

  if (currentPlayer == player1 || selectedPieceValue == 6) {
    if (initIndex / 8 < 7) {
      if (initIndex % 8 > 0) {
        if (!otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 7)) && !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 7))) {
          allowedTiles.push_back(getTileAtIndex(initIndex + 7));
        }
        if (!otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 9)) && !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 9))) {
          allowedTiles.push_back(getTileAtIndex(initIndex + 9));
        }
      }
    }
  } else if (currentPlayer == player2 || selectedPieceValue == 6) {

  }
}

void State_Game::update() {
  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);

  player1.updatePositionByTileSize(tileSize);
  player2.updatePositionByTileSize(tileSize);
}

void State_Game::render() {
  for (auto & tile : board) {
    ctx.window.draw(tile);
  }
  for (auto & tile : allowedTiles) {
    ctx.window.draw(tile);
  }
  player1.draw(ctx.window);
  player2.draw(ctx.window);
}
