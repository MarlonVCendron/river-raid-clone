#ifndef RIVERRAID_BULLETSPAWNER_H
#define RIVERRAID_BULLETSPAWNER_H

#include <list>
#include <glm/glm.hpp>
#include "../Bullet/Bullet.cpp"

class BulletSpawner {

private:
  std::list<Bullet*> bullets;
  float bulletCooldown = 0.0f;

public:
  BulletSpawner();
  void update();
  void render();
  void spawnBullet(glm::vec2 position);
  std::list<Bullet*> getBullets();
};

#endif
