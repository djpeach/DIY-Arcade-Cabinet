#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "State_Base.hpp"
#include "Player.hpp"

struct SharedContext;

class State_Game : public State_Base {
public:
  State_Game(SharedContext & ctx);
  ~State_Game();

  void handleEvent(sf::Event e);
  void update();
  void render();
private:
  void selectPiece();
  Tile getTileAtIndex(int i);
  void calcAllowedTiles(Player & currentPlayer, Player & otherPlayer);

  std::vector<Tile> board;
  std::vector<Tile> allowedTiles;
  Player player1, player2;
};
