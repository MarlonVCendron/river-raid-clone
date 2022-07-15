#ifndef RIVERRAID_BRIDGE_H
#define RIVERRAID_BRIDGE_H

#include "../Player/Player.h"

class Bridge {

private:
  float h = 100.0;
  int bulletCount = 0;

public:
  float x = 0.0, offsetY;
  float* y;

  Bridge(float* y, float boundHeight);
  int update(std::list<Bullet*>& bullets, Player* player);
  void render();
  bool checkPlayerCollision(Player* player);
  bool checkBulletsCollision(std::list<Bullet*>& bullets);
};

#endif
