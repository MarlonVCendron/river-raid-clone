#ifndef RIVERRAID_BULLET_H
#define RIVERRAID_BULLET_H

#include <glm/glm.hpp>

class Bullet {

private:
  glm::vec2 position;
  float speed = 20.0f;

public:
  Bullet(glm::vec2 position);
  void update();
  void render();
};

#endif
