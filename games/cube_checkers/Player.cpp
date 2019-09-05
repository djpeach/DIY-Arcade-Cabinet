#include <exception>
#include <cmath>
#include <iostream>

#include "Player.hpp"

Player::Player() :
selectedPiece(nullptr),
score(0) {}

void Player::setTile(Tile tile) {
  curTile = tile;
}

void Player::updatePositionByTileSize(sf::Vector2f tileSize) {
  curTile.setPosition(sf::Vector2f(tileSize.x * (curTile.index % 8), tileSize.y * floor(curTile.index / 8)));
}

void Player::draw(sf::RenderWindow & window) {
  window.draw(curTile);
  for (int i=0;i<pieces.size();i++) {
    pieces[i].draw(window);
  }
}

void Player::addCube(Cube cube) {
  pieces.push_back(cube);
}

void Player::selectPiece() {
  if (selectedPiece) {
    selectedPiece->unhighlight();
  }

  sf::FloatRect curTileBounds = curTile.getBounds();
  for (int i=0;i<pieces.size();i++) {
    sf::FloatRect pieceBounds = pieces[i].getBounds();
    if (pieceBounds.left >= curTileBounds.left &&
        pieceBounds.top >= curTileBounds.top &&
        pieceBounds.left + pieceBounds.width < curTileBounds.left + curTileBounds.width &&
        pieceBounds.top + pieceBounds.height < curTileBounds.top + curTileBounds.height) {
      pieces[i].highlight();
      selectedPiece = &pieces[i];
    }
  }
}

Cube * Player::getPieceOnTile(Tile tile) {
  for (auto & piece : pieces) {
    if (piece.index == tile.index) {
      return &piece;
    }
  }
  return nullptr;
}

void Player::capturePiece(Cube * piece) {
  score += piece->value;
  selectedPiece->setPosition(piece->getPosition());
  selectedPiece->unhighlight();
  selectedPiece = nullptr;
}

void Player::movePiece() {
  selectedPiece->setPosition(curTile.getPosition());
  selectedPiece->index = curTile.index;
  selectedPiece->unhighlight();
  selectedPiece = nullptr;
}

void Player::removePiece(Cube * piece) {
  sf::FloatRect pieceToRemoveBounds = piece->getBounds();
  for (int i=0;i<pieces.size();i++) {
    sf::FloatRect pieceBounds = pieces[i].getBounds();
    if (pieceBounds.left >= pieceToRemoveBounds.left &&
        pieceBounds.top >= pieceToRemoveBounds.top &&
        pieceBounds.left + pieceBounds.width <= pieceToRemoveBounds.left + pieceToRemoveBounds.width &&
        pieceBounds.top + pieceBounds.height <= pieceToRemoveBounds.top + pieceToRemoveBounds.height) {
      pieces.erase(pieces.begin() + i);
    }
  }
}

bool Player::operator== (const Player & rhs) {
  return this->name == rhs.name;
}
