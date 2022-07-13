#ifndef RIVERRAID_BULLET_H
#define RIVERRAID_BULLET_H

#include <glm/glm.hpp>

class Bullet {

private:
  float speed = 20.0f;

public:
  float size = 10.0;
  glm::vec2 position;
  Bullet(glm::vec2 position);
  bool update();
  void render();
};

#endif
