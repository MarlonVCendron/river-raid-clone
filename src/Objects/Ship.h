#ifndef RIVERRAID_SHIP_H
#define RIVERRAID_SHIP_H

#include "../Player/Player.h"

class Ship {

private:
  float boundX1, boundX2;
  float w = 120.0, h = 40.0;
  float speed;

public:
  float x, offsetY;
  float* y;

  Ship(float boundX1, float boundX2, float* y, float boundHeight, float speed);
  int update(std::list<Bullet*>& bullets, Player* player);
  void render();
  bool checkPlayerCollision(Player* player);
  bool checkBulletsCollision(std::list<Bullet*>& bullets);
};

#endif
