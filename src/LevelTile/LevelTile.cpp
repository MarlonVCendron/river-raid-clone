#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "LevelTile.h"

#define X_MIDDLE glutGet(GLUT_WINDOW_WIDTH) / 2.0f

LevelTile::LevelTile(float y, float* speed, float x1, float x2, float prevX1, float prevX2) {
  this->y = y;
  this->speed = speed;
  this->x1 = x1;
  this->x2 = x2;
  this->prevX1 = prevX1;
  this->prevX2 = prevX2;

  if(x1 == prevX1){
    this->height = randomFloat(glutGet(GLUT_WINDOW_HEIGHT) * 0.6f) + 500.0f;
    if(y !=0 ) this->spawnObjects();
  }else {
    this->height = 200.0f;
    //this->height = randomFloat(glutGet(GLUT_WINDOW_HEIGHT) * 0.5f) + 100;
   }
}

void LevelTile::spawnObjects() {
  if(rand() % 10 == 0)
    return this->bridges.push_back(new Bridge(&y, height));
  
  int totalShips = (int) randomFloat(height/200.0) + 1;
  int totalHelis = (int) randomFloat(height/200.0) + 1;
  int totalFuels = (int) randomFloat(height/500.0) + 1;

  for (int i=0; i<totalShips; i++)
    this->ships.push_back(new Ship(x1, x2, &y, height, 3.0f));
  for (int i=0; i<totalHelis; i++)
    this->helis.push_back(new Heli(x1, x2, &y, height, 5.0f));
  for (int i=0; i<totalFuels; i++)
    this->fuels.push_back(new Fuel(x1, x2, &y, height));
}

int LevelTile::update(std::list<Bullet*>& bullets, Player* player){
  bool playerDeath = false;
  ships.remove_if([&](Ship* ship) {
    int shipStatus = ship->update(bullets, player);
    if(shipStatus == 1) playerDeath = true;
    bool destroy = shipStatus != 0;
    if(destroy) {
      SoundController::play("explosion");
      player->score += 10;
    }
    return destroy;
  });

  helis.remove_if([&](Heli* heli) {
    int heliStatus = heli->update(bullets, player);
    if(heliStatus == 1) playerDeath = true;
    bool destroy = heliStatus != 0;
    if(destroy) {
      SoundController::play("explosion");
      player->score += 10;
    }
    return destroy;
  });

  fuels.remove_if([&](Fuel* fuel) {
    int fuelStatus = fuel->update(bullets, player);
    if(fuelStatus == 1) player->fillTank();
    bool destroy = fuelStatus == 2;
    if(destroy) {
      SoundController::play("explosion");
      player->score += 10;
    }
    return destroy;
  });

  bridges.remove_if([&](Bridge* bridge) {
    int bridgeStatus = bridge->update(bullets, player);
    if(bridgeStatus == 1) playerDeath = true;
    bool destroy = bridgeStatus == 2;
    if(destroy) {
      SoundController::play("explosion");
      player->score += 100;
    }
    return destroy;
  });

  this->y -= *this->speed;

  if(this->y + this->height < 0) return 1;
  if(playerDeath) return 2;
  return 0;
}

float getx(float x1, float y1, float x2, float y2, float p) {
  float a = y1-y2;
  float b = x2-x1;
  float c = (x1-x2)*y1 + (y2-y1)*x1;
  return (b*(y2-p) + c)/(-a);
}

void LevelTile::render() {
  float p = 10.0;
  float bX1 = getx(x1, y+height, prevX1, y, p);
  float bX2 = getx(x2, y+height, prevX2, y, p);

  glColor3f(0, 0.26, 0.82);
  glBegin(GL_POLYGON);
  glVertex2f(bX1, y-p);
  glVertex2f(x1, y+height);
  glVertex2f(x2, y+height);
  glVertex2f(bX2, y-p);
  glEnd();

  glColor3f(0, 0.3, 0);
  glBegin(GL_POLYGON);
  glVertex2f(0, y-p);
  glVertex2f(0, y+height);
  glVertex2f(x1, y+height);
  glVertex2f(bX1, y-p);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(bX2, y-p);
  glVertex2f(x2, y+height);
  glVertex2f(glutGet(GLUT_WINDOW_WIDTH), y+height);
  glVertex2f(glutGet(GLUT_WINDOW_WIDTH), y-p);
  glEnd();

  for (auto const& ship : this->ships)
    ship->render(); 
  for (auto const& heli : this->helis)
    heli->render(); 
  for (auto const& fuel : this->fuels)
    fuel->render(); 
  for (auto const& bridge : this->bridges)
    bridge->render(); 
}

bool LevelTile::checkPlayerCollision(Player* player) {
  bool collideLeft, collideRight;
  if(x1 == prevX1) {
    collideLeft = boxCollision(
      0, this->y, this->x1, this->height,
      player->position.x, player->position.y, player->w, player->h
    );

    collideRight = boxCollision(
      this->x2, this->y, glutGet(GLUT_WINDOW_WIDTH), this->height,
      player->position.x, player->position.y, player->w, player->h
    );

  } else {
    collideLeft = lineBoxCollision(
      this->prevX1, this->y, this->x1, this->y + this->height,
      player->position.x, player->position.y, player->w, player->h,
      true
    );

    collideRight = lineBoxCollision(
      this->prevX2, this->y, this->x2, this->y + this->height,
      player->position.x, player->position.y, player->w, player->h,
      false
    );
  }
  return collideLeft || collideRight;
}

