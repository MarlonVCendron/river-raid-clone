#ifndef RIVERRAID_LEVELTILE_H
#define RIVERRAID_LEVELTILE_H

#include <glm/glm.hpp>

class LevelTile {

private:
  float y;
  float speed;
  float width;
  float height;

public:
  float getTopY() { return y + height; }

  LevelTile(float y, float speed, float height);
  bool update();
  void render();
};

#endif
