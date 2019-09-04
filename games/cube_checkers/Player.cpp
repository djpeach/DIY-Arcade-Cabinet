#include <exception>
#include <cmath>

#include "Player.hpp"

Player::Player() :
selectedPiece(nullptr),
pieceIsSelected(false) {}

void Player::setTile(Tile tile) {
  curTile = tile;
}

void Player::updatePositionByTileSize(sf::Vector2f tileSize) {
  curTile.setPosition(sf::Vector2f(tileSize.x * (index % 8), tileSize.y * floor(index / 8)));
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
  sf::FloatRect curTileBounds = tile.getBounds();
  for (int i=0;i<pieces.size();i++) {
    sf::FloatRect pieceBounds = pieces[i].getBounds();
    if (pieceBounds.left >= curTileBounds.left &&
        pieceBounds.top >= curTileBounds.top &&
        pieceBounds.left + pieceBounds.width < curTileBounds.left + curTileBounds.width &&
        pieceBounds.top + pieceBounds.height < curTileBounds.top + curTileBounds.height) {
      return &pieces[i];
    }
  }
  return nullptr;
}
