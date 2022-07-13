#ifndef RIVERRAID_SHIP_H
#define RIVERRAID_SHIP_H

#include "../Player/Player.h"

class Ship {

private:
  float x, offsetY;
  float* y;
  float boundX1, boundX2;
  float w = 50.0, h = 50.0;
  float speed;

public:
  Ship(float boundX1, float boundX2, float* y, float boundHeight, float speed);
  bool update(std::list<Bullet*> bullets, Player* player);
  void render();
  bool checkPlayerCollision(Player* player);
  bool checkBulletsCollision(std::list<Bullet*> bullets);
};

#endif
