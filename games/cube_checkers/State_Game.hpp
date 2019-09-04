#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "State_Base.hpp"
#include "Tile.hpp"

struct SharedContext;

class State_Game : public State_Base {
public:
  State_Game(SharedContext & ctx);
  ~State_Game();

  void handleEvent(sf::Event e);
  void update();
  void render();
private:
  std::vector<Tile> board;
  int curPlayer;
  int player1Index, player2Index;
  Tile player1Tile, player2Tile;
};
