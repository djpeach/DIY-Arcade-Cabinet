#include <cmath>

#include "Player.hpp"

Player::Player() {}

void Player::setTile(Tile tile) {
  curTile = tile;
}

void Player::updatePositionByTileSize(sf::Vector2f tileSize) {
  curTile.setPosition(sf::Vector2f(tileSize.x * (index % 8), tileSize.y * floor(index / 8)));
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(curTile, states);
  for (int i=0;i<pieces.size();i++) {
    target.draw(pieces[i], states);
  }
}

void Player::addCube(Cube cube) {
  pieces.push_back(cube);
}
