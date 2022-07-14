#ifndef RIVERRAID_PLAYER_H
#define RIVERRAID_PLAYER_H

#include <glm/glm.hpp>
#include "../BulletSpawner/BulletSpawner.cpp"

class Player {

private:
  int direction = 0;
  float speed = 5.0f;
  BulletSpawner* bulletSpawner = new BulletSpawner();

public:
  glm::vec2 position;
  float w, h;

  Player(glm::vec2 position);
  void update();
  void render();
  void reset();
  void keyDown(unsigned char key, int x, int y);
  void keyUp(unsigned char key, int x, int y);
  std::list<Bullet*>& getBullets();
};

#endif
