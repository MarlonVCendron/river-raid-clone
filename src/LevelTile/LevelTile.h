#ifndef RIVERRAID_LEVELTILE_H
#define RIVERRAID_LEVELTILE_H

#include "../Player/Player.cpp"

class LevelTile {

private:
  float y;
  float* speed;
  float x1;
  float x2;
  float prevX1 = 0.0f;
  float prevX2 = 0.0f;
  float height;

public:
  float getTopY() { return y + height; }

  LevelTile(float y, float* speed, float x1, float x2, float prevX1, float prevX2);
  bool update(std::list<Bullet*> bullets);
  void render();
  bool checkPlayerCollision(Player* player);
};

#endif
