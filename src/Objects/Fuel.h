#ifndef RIVERRAID_FUEL_H
#define RIVERRAID_FUEL_H

#include "../Player/Player.h"

class Fuel {

private:
  float boundX1, boundX2;
  float w = 40.0, h = 70.0;

public:
  float x, offsetY;
  float* y;

  Fuel(float boundX1, float boundX2, float* y, float boundHeight);
  int update(std::list<Bullet*>& bullets, Player* player);
  void render();
  bool checkPlayerCollision(Player* player);
  bool checkBulletsCollision(std::list<Bullet*>& bullets);
};

#endif
