#include <cmath>

#include "Player.hpp"

#include <iostream>

Player::Player() {}

void Player::setTile(Tile tile) {
  curTile = tile;
}

void Player::updatePositionByTileSize(sf::Vector2f tileSize) {
  curTile.setPosition(sf::Vector2f(tileSize.x * (index % 8), tileSize.y * floor(index / 8)));
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const {
  target.draw(curTile, states);
}
