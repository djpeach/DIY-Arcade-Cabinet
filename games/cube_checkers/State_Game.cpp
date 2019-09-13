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
        cube.index = i;
        player1.addCube(cube);
      } else if ((i / 8) > 4) {
        Cube cube = Cube(tileSize * 0.8f, sf::Vector2f(tilePosition.x + tileSize.x / 2, tilePosition.y + tileSize.y / 2), sf::Color(20, 20, 20));
        cube.index = i;
        player2.addCube(cube);
      }
    }
    sf::Color tileColor = sf::Color(whiteHue, whiteHue, whiteHue);
    Tile tile(tileSize, tilePosition, tileColor);
    tile.index = i;
    board.push_back(tile);

    if (i == 1) {
      tile.setColor(sf::Color(200, 15, 15, 120));
      player1.setTile(tile);
    } else if (i == 62) {
      tile.setColor(sf::Color(50, 50, 50, 100));
      player2.setTile(tile);
    }

  }

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
          player1.curTile.index = player1.curTile.index - 8 >= 0 ? player1.curTile.index - 8 : player1.curTile.index + 56;
          break;
        case sf::Keyboard::S:
          player1.curTile.index = player1.curTile.index + 8 <= 63 ? player1.curTile.index + 8 : player1.curTile.index - 56;
          break;
        case sf::Keyboard::A:
          player1.curTile.index = player1.curTile.index % 8 == 0 ? player1.curTile.index + 7 : player1.curTile.index - 1;
          break;
        case sf::Keyboard::D:
          player1.curTile.index = (player1.curTile.index + 1) % 8 == 0 ? player1.curTile.index - 7 : player1.curTile.index + 1;
          break;
        case sf::Keyboard::F:
          selectPiece();
        default:
          break;
      }
    } else if (player2.isTurn) {
      switch (e.key.code) {
        case sf::Keyboard::I:
          player2.curTile.index = player2.curTile.index - 8 >= 0 ? player2.curTile.index - 8 : player2.curTile.index + 56;
          break;
        case sf::Keyboard::K:
          player2.curTile.index = player2.curTile.index + 8 <= 63 ? player2.curTile.index + 8 : player2.curTile.index - 56;
          break;
        case sf::Keyboard::J:
          player2.curTile.index = player2.curTile.index % 8 == 0 ? player2.curTile.index + 7 : player2.curTile.index - 1;
          break;
        case sf::Keyboard::L:
          player2.curTile.index = (player2.curTile.index + 1) % 8 == 0 ? player2.curTile.index - 7 : player2.curTile.index + 1;
          break;
        case sf::Keyboard::H:
          selectPiece();
        default:
          break;
      }
    }
  }
}

void State_Game::update() {
  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);

  getPotentialJumps();

  player1.updatePositionByTileSize(tileSize);
  player2.updatePositionByTileSize(tileSize);
}

void State_Game::render() {
  for (auto & tile : board) {
    ctx.window.draw(tile);
  }
  for (auto & tile : allowedMoves) {
    tile.setColor(sf::Color(15, 200, 15, 100));
    ctx.window.draw(tile);
  }
  for (auto & tile : potentialJumps) {
    tile.setColor(sf::Color(130, 200, 250));
    ctx.window.draw(tile);
  }
  player1.draw(ctx.window);
  player2.draw(ctx.window);
}

void State_Game::selectPiece() {
  Player & currentPlayer = player1.isTurn ? player1 : player2;
  Player & otherPlayer = player1.isTurn ? player2 : player1;
  Cube * pieceOnSelectedTile;

  // leave to view indexes easily
  std::cout << "tile index: " << currentPlayer.curTile.index << std::endl;

  getPotentialJumps();

  if (currentPlayer.getPieceOnTile(currentPlayer.curTile)) {
    bool canSelect = false;
    if (potentialJumps.empty()) {
      canSelect = true;
    } else {
      for (auto tile : potentialJumps) {
        if (tile.index == currentPlayer.curTile.index) {
          canSelect = true;
        }
      }
    }
    if (canSelect) {
      currentPlayer.selectPiece();
      calcallowedMoves(currentPlayer, otherPlayer);
    }
  } else if (currentPlayer.selectedPiece) {
    for (auto & allowedTile : allowedMoves) {
      if (allowedTile.index == currentPlayer.curTile.index) {

        if (abs(currentPlayer.curTile.index - currentPlayer.selectedPiece->index) > 9) {
          currentPlayer.capturePiece(otherPlayer.getPieceOnTile(getTileAtIndex(currentPlayer.selectedPiece->index + ((currentPlayer.curTile.index - currentPlayer.selectedPiece->index) / 2))));
          otherPlayer.removePiece(otherPlayer.getPieceOnTile(getTileAtIndex(currentPlayer.selectedPiece->index + ((currentPlayer.curTile.index - currentPlayer.selectedPiece->index) / 2))));
          getPotentialJumpsForTile(currentPlayer.curTile);
        }

        currentPlayer.movePiece();
        allowedMoves.clear();

        if (potentialJumps.empty()) {
          player1.isTurn = !player1.isTurn;
          player2.isTurn = !player2.isTurn;
        }

        break;
      }
    }
  }
}

Tile State_Game::getTileAtIndex(int i) {
  sf::Vector2u windowSize = ctx.window.getSize();
  sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);
  sf::Vector2f tilePosition(tileSize.x * (i % 8), tileSize.y * floor(i / 8));
  Tile tile(tileSize, tilePosition, sf::Color::White);
  tile.index = i;
  return tile;
}

void State_Game::calcallowedMoves(Player & currentPlayer, Player & otherPlayer) {
  allowedMoves.clear();
  int initIndex = currentPlayer.selectedPiece->index;
  int selectedPieceValue = currentPlayer.selectedPiece->value;

  if (currentPlayer == player1 || selectedPieceValue == 6) { // additions - downs
    if (initIndex / 8 < 6) { // can check two rows down
      if ((initIndex - 1) % 8 > 0) { // can check two cols left
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 7)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 14)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 14))) { // can jump opponent's piece left
          allowedMoves.push_back(getTileAtIndex(initIndex + 14));
        }
      }
      if ((initIndex + 2) % 8 > 0) { // can check two cols right
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 9)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 18)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 18))) { // can jump opponent's piece right
          allowedMoves.push_back(getTileAtIndex(initIndex + 18));
        }
      }
    }
    if (allowedMoves.empty() && initIndex / 8 < 7) { // can check at least one row down
      if (initIndex % 8 > 0) { // can check at least one col left
        if (!otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 7)) &&
           !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 7))) { // no pieces in the way
          allowedMoves.push_back(getTileAtIndex(initIndex + 7));
        }
      }
      if ((initIndex + 1) % 8 > 0) { // can check at least one col right
        if (!otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 9)) &&
           !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 9))) { // no pieces in the way
          allowedMoves.push_back(getTileAtIndex(initIndex + 9));
        }
      }
    }
  }
  if (currentPlayer == player2 || selectedPieceValue == 6) { // subtractions - ups
    if (initIndex / 8 > 1) { // can check two rows up
      if ((initIndex - 1) % 8 > 0) { // can check two cols left
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 9)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 18)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 18))) { // can jump opponent's piece left
          allowedMoves.push_back(getTileAtIndex(initIndex - 18));
        }
      }
      if ((initIndex + 2) % 8 > 0) { // can check two cols right
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 7)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 14)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 14))) { // can jump opponent's piece right
          allowedMoves.push_back(getTileAtIndex(initIndex - 14));
        }
      }
    }
    if (allowedMoves.empty() && initIndex / 8 > 0) { // can check at least one row up
      if (initIndex % 8 > 0) { // can check at least one col left
        if (!otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 9)) &&
           !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 9))) { // no pieces in the way
          allowedMoves.push_back(getTileAtIndex(initIndex - 9));
        }
      }
      if ((initIndex + 1) % 8 > 0) { // can check at least one col right
        if (!otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 7)) &&
           !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 7))) { // no pieces in the way
          allowedMoves.push_back(getTileAtIndex(initIndex - 7));
        }
      }
    }
  }
}

void State_Game::getPotentialJumps() {
  potentialJumps.clear();

  Player & currentPlayer = player1.isTurn ? player1 : player2;
  Player & otherPlayer = player1.isTurn ? player2 : player1;

  for (auto piece : currentPlayer.pieces) {
    int initIndex = piece.index;
    if (piece.value == 6 || currentPlayer == player1) { // checking downward
      if (initIndex / 8 < 6) { // can check two rows down
        if ((initIndex - 1) % 8 > 0) { // can check two cols left
          if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 7)) &&
              !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 14)) &&
              !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 14))) { // can jump opponent's piece left
            potentialJumps.push_back(getTileAtIndex(initIndex));
          }
        }
        if ((initIndex + 2) % 8 > 0) { // can check two cols right
          if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 9)) &&
              !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 18)) &&
              !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 18))) { // can jump opponent's piece right
            potentialJumps.push_back(getTileAtIndex(initIndex));
          }
        }
      }
    }
    if (piece.value == 6 || currentPlayer == player2) { // checking upward
      if (initIndex / 8 > 1) { // can check two rows up
        if ((initIndex - 1) % 8 > 0) { // can check two cols left
          if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 9)) &&
              !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 18)) &&
              !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 18))) { // can jump opponent's piece left
            potentialJumps.push_back(getTileAtIndex(initIndex));
          }
        }
        if ((initIndex + 2) % 8 > 0) { // can check two cols right
          if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 7)) &&
              !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 14)) &&
              !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 14))) { // can jump opponent's piece right
            potentialJumps.push_back(getTileAtIndex(initIndex));
          }
        }
      }
    }
  }
}

void State_Game::getPotentialJumpsForTile(Tile tile) {
  potentialJumps.clear();

  Player & currentPlayer = player1.isTurn ? player1 : player2;
  Player & otherPlayer = player1.isTurn ? player2 : player1;
  int initIndex = tile.index;

  if (currentPlayer.selectedPiece->value == 6 || currentPlayer == player1) { // checking downward
    if (initIndex / 8 < 6) { // can check two rows down
      if ((initIndex - 1) % 8 > 0) { // can check two cols left
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 7)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 14)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 14))) { // can jump opponent's piece left
          potentialJumps.push_back(getTileAtIndex(initIndex));
        }
      }
      if ((initIndex + 2) % 8 > 0) { // can check two cols right
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 9)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex + 18)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex + 18))) { // can jump opponent's piece right
          potentialJumps.push_back(getTileAtIndex(initIndex));
        }
      }
    }
  }
  if (currentPlayer.selectedPiece->value == 6 || currentPlayer == player2) { // checking upward
    if (initIndex / 8 > 1) { // can check two rows up
      if ((initIndex - 1) % 8 > 0) { // can check two cols left
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 9)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 18)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 18))) { // can jump opponent's piece left
          potentialJumps.push_back(getTileAtIndex(initIndex));
        }
      }
      if ((initIndex + 2) % 8 > 0) { // can check two cols right
        if (otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 7)) &&
            !otherPlayer.getPieceOnTile(getTileAtIndex(initIndex - 14)) &&
            !currentPlayer.getPieceOnTile(getTileAtIndex(initIndex - 14))) { // can jump opponent's piece right
          potentialJumps.push_back(getTileAtIndex(initIndex));
        }
      }
    }
  }
}
