#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Cube.hpp"

class Player {
public:
  bool isTurn;
  Tile curTile;
  Cube * selectedPiece;
  std::string name;

  Player();

  void setTile(Tile tile);
  void updatePositionByTileSize(sf::Vector2f tileSize);

  void addCube(Cube cube);

  void selectPiece();
  Cube * getPieceOnTile(Tile tile);
  void capturePiece(Cube * piece);
  void removePiece(Cube * piece);
  void movePiece();

  void draw(sf::RenderWindow & window);

  bool operator== (const Player & rhs);
private:
  std::vector<Cube> pieces;
  int score;
};
