#ifndef RIVERRAID_PLAYER_H
#define RIVERRAID_PLAYER_H

#include <glm/glm.hpp>
#include "../BulletSpawner/BulletSpawner.cpp"

class Player {

private:
  glm::vec2 position;
  int direction = 0;
  float speed = 5.0f;
  BulletSpawner* bulletSpawner = new BulletSpawner();

public:
  Player(glm::vec2 position);
  void update();
  void render();
  void keyDown(unsigned char key, int x, int y);
  void keyUp(unsigned char key, int x, int y);
};

#endif
