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
  this->ships.push_back(new Ship(x1, x2, &y, height, 3.0f));
  this->helis.push_back(new Heli(x1, x2, &y, height, 5.0f));
}

int LevelTile::update(std::list<Bullet*>& bullets, Player* player){
  bool playerDeath = false;
  ships.remove_if([&](Ship* ship) {
    int shipStatus = ship->update(bullets, player);
    if(shipStatus == 1) playerDeath = true;
    return (shipStatus != 0);
  });

  helis.remove_if([&](Heli* heli) {
    int heliStatus = heli->update(bullets, player);
    if(heliStatus == 1) playerDeath = true;
    return (heliStatus != 0);
  });

  this->y -= *this->speed;

  if(this->y + this->height < 0) return 1;
  if(playerDeath) return 2;
  return 0;
}

void LevelTile::render() {
  glColor3f(0, 0.26, 0.82);
  glBegin(GL_POLYGON);
  glVertex2f(this->prevX1, this->y);
  glVertex2f(this->x1, this->y+this->height);
  glVertex2f(this->x2, this->y+this->height);
  glVertex2f(this->prevX2, this->y);
  glEnd();

  glColor3f(0, 0.3, 0);
  glBegin(GL_POLYGON);
  glVertex2f(0, this->y);
  glVertex2f(0, this->y+this->height);
  glVertex2f(this->x1, this->y+this->height);
  glVertex2f(this->prevX1, this->y);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(this->prevX2, this->y);
  glVertex2f(this->x2, this->y+this->height);
  glVertex2f(glutGet(GLUT_WINDOW_WIDTH), this->y+this->height);
  glVertex2f(glutGet(GLUT_WINDOW_WIDTH), this->y);
  glEnd();

  for (auto const& ship : this->ships)
    ship->render(); 
  for (auto const& heli : this->helis)
    heli->render(); 
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

