#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "LevelTile.h"
#include "../Utils/RandomNumber.cpp"
#include "../Utils/checkCollision.cpp"

#include <iostream>

#define X_MIDDLE glutGet(GLUT_WINDOW_WIDTH) / 2.0f

LevelTile::LevelTile(float y, float* speed) {
  this->y = y;
  this->speed = speed;
  this->height = randomFloat(glutGet(GLUT_WINDOW_HEIGHT) * 0.6f) + 500;
  this->width = randomFloat(glutGet(GLUT_WINDOW_WIDTH) * 0.7f) + 200;
}

bool LevelTile::update(std::list<Bullet*> bullets) {
  this->y -= *this->speed;

  if(this->y + this->height < 0) return false;
  return true;
}

void LevelTile::render() {
  float leftX  = X_MIDDLE-this->width/2.0f;
  float rightX = X_MIDDLE+this->width/2.0f;

  glColor3f(0, 0.26, 0.82);
  glBegin(GL_POLYGON);
  glVertex2f(leftX, this->y);
  glVertex2f(leftX, this->y+this->height);
  glVertex2f(rightX, this->y+this->height);
  glVertex2f(rightX, this->y);
  glEnd();

  glColor3f(0, 0.3, 0);
  glBegin(GL_POLYGON);
  glVertex2f(0, this->y);
  glVertex2f(0, this->y+this->height);
  glVertex2f(leftX, this->y+this->height);
  glVertex2f(leftX, this->y);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(rightX, this->y);
  glVertex2f(rightX, this->y+this->height);
  glVertex2f(X_MIDDLE*2, this->y+this->height);
  glVertex2f(X_MIDDLE*2, this->y);
  glEnd();
}

bool LevelTile::checkPlayerCollision(Player* player) {
  float width = X_MIDDLE-this->width/2.0f;
  float xRight = X_MIDDLE+this->width/2.0f;

  bool collideLeft = checkCollision(
    0, this->y, width, this->height, // Left
    player->position.x, player->position.y, player->w, player->h // Player
  );

  bool collideRight = checkCollision(
    xRight, this->y, width, this->height, // Right
    player->position.x, player->position.y, player->w, player->h // Player
  );

  return collideLeft || collideRight;
}

