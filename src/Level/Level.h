#ifndef RIVERRAID_LEVEL_H
#define RIVERRAID_LEVEL_H

#include <glm/glm.hpp>
#include <list>
#include "../LevelTile/LevelTile.cpp"

class Level {

private:
  Player* player;
  std::list<LevelTile*> tiles;
  float speed = 5.0f;
  float prevX1;
  float prevX2;
  bool connector;

  bool tryAddTile();

public:
  Level(Player* player);
  bool update();
  void render();
  void endGame();
};

#endif
