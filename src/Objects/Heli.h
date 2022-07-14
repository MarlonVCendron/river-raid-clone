#ifndef RIVERRAID_HELI_H
#define RIVERRAID_HELI_H

#include "../Player/Player.h"

class Heli {

private:
  float x, offsetY;
  float* y;
  float boundX1, boundX2;
  float w = 60.0, h = 50.0;
  float speed;
  int counter;
  bool animationFrame;

public:
  Heli(float boundX1, float boundX2, float* y, float boundHeight, float speed);
  int update(std::list<Bullet*>& bullets, Player* player);
  void render();
  bool checkPlayerCollision(Player* player);
  bool checkBulletsCollision(std::list<Bullet*>& bullets);
};

#endif
