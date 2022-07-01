#ifndef RIVERRAID_LEVELTILECONNECTOR_H
#define RIVERRAID_LEVELTILECONNECTOR_H

#include "../Player/Player.cpp"

class LevelTileConnector {

private:
  float y;
  float* speed;
  float height;
  float x1;
  float x2;

public:
  float getTopY() { return y + height; }

  LevelTileConnector(float y, float* speed);
  bool update(std::list<Bullet*> bullets);
  void render();
  bool checkPlayerCollision(Player* player);
};

#endif
