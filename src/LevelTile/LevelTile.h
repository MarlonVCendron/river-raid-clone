#ifndef RIVERRAID_LEVELTILE_H
#define RIVERRAID_LEVELTILE_H

#include <glm/glm.hpp>

class LevelTile {

private:
  float y;
  float speed;
  float width;
  const float height = 100.0f;

public:
  LevelTile(float y, float speed);
  bool update();
  void render();
};

#endif
