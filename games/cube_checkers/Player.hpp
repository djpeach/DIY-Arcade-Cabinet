#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Cube.hpp"

class Player : public sf::Drawable {
public:
  bool isTurn;
  int index;

  Player();

  void setTile(Tile tile);
  void updatePositionByTileSize(sf::Vector2f tileSize);

  void addCube(Cube cube);

  void draw(sf::RenderTarget & target, sf::RenderStates states) const;
private:
  Tile curTile;
public:
  std::vector<Cube> pieces;
};
