#ifndef RIVERRAID_LEVELTILE_H
#define RIVERRAID_LEVELTILE_H

#include "../Player/Player.cpp"

class LevelTile {

private:
  float y;
  float* speed;
  float width;
  float height;

public:
  float getTopY() { return y + height; }

  LevelTile(float y, float* speed);
  bool update(std::list<Bullet*> bullets);
  void render();
  bool checkPlayerCollision(Player* player);
};

#endif
