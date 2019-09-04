#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Cube.hpp"

class Player {
public:
  bool isTurn;
  int index;
  Tile curTile;
  Cube * selectedPiece;

  Player();

  void setTile(Tile tile);
  void updatePositionByTileSize(sf::Vector2f tileSize);

  void addCube(Cube cube);

  void selectPiece();
  Cube * getPieceOnTile(Tile tile);

  void draw(sf::RenderWindow & window);
private:
  bool pieceIsSelected;
  std::vector<Cube> pieces;
};
