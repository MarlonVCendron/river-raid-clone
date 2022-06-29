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

  bool tryAddTile();

public:
  Level(Player* player);
  bool update();
  void render();
};

#endif
