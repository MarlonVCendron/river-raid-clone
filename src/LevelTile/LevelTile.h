#ifndef RIVERRAID_LEVELTILE_H
#define RIVERRAID_LEVELTILE_H

#include "../Player/Player.cpp"
#include "../Objects/Ship.cpp"
#include "../Objects/Heli.cpp"
#include "../Objects/Fuel.cpp"
#include "../Objects/Bridge.cpp"

class LevelTile {

private:
  float y;
  float* speed;
  float x1, x2;
  float prevX1 = 0.0f;
  float prevX2 = 0.0f;
  float height;
  std::list<Ship*> ships;
  std::list<Heli*> helis;
  std::list<Fuel*> fuels;
  std::list<Bridge*> bridges;

  void spawnObjects();

public:
  float getTopY() { return y + height; }

  LevelTile(float y, float* speed, float x1, float x2, float prevX1, float prevX2);
  int update(std::list<Bullet*>& bullets, Player* player);
  void render();
  bool checkPlayerCollision(Player* player);
};

#endif
