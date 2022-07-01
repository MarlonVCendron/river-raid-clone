#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "LevelTile.h"
#include "../Utils/RandomNumber.cpp"
#include "../Utils/checkCollision.cpp"

#include <iostream>

#define X_MIDDLE glutGet(GLUT_WINDOW_WIDTH) / 2.0f

LevelTile::LevelTile(float y, float* speed, float x1, float x2, float prevX1, float prevX2) {
  this->y = y;
  this->speed = speed;
  this->x1 = x1;
  this->x2 = x2;
  this->prevX1 = prevX1;
  this->prevX2 = prevX2;

  if(x1 == prevX1)
    this->height = randomFloat(glutGet(GLUT_WINDOW_HEIGHT) * 0.6f) + 500.0f;
  else
    this->height = 200.0f;
    //this->height = randomFloat(glutGet(GLUT_WINDOW_HEIGHT) * 0.5f) + 100;
}

bool LevelTile::update(std::list<Bullet*> bullets) {
  this->y -= *this->speed;

  if(this->y + this->height < 0) return false;
  return true;
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
}

bool LevelTile::checkPlayerCollision(Player* player) {
  if(x1 == prevX1) {
    bool collideLeft = checkCollision(
      0, this->y, this->x1, this->height, // Left
      player->position.x, player->position.y, player->w, player->h // Player
    );

    bool collideRight = checkCollision(
      this->x2, this->y, glutGet(GLUT_WINDOW_WIDTH), this->height, // Right
      player->position.x, player->position.y, player->w, player->h // Player
    );

    return collideLeft || collideRight;
  } else {
    return false;
  }
}

