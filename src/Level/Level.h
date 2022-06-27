#ifndef RIVERRAID_LEVEL_H
#define RIVERRAID_LEVEL_H

#include <glm/glm.hpp>
#include <list>
#include "../LevelTile/LevelTile.cpp"

class Level {

private:
  float speed = 5.0f;
  std::list<LevelTile*> tiles;

  bool tryAddTile();

public:
  Level();
  void update();
  void render();
};

#endif
