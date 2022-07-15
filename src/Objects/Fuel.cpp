#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Fuel.h"
#include "../Utils/checkCollision.h"
#include "../Utils/RandomNumber.h"

Fuel::Fuel(float boundX1, float boundX2, float* y, float boundHeight) {
  this->x = boundX1+randomFloat(boundX2-boundX1-100);
  this->y = y;
  this->boundX1 = boundX1;
  this->boundX2 = boundX2;
  this->offsetY = randomFloat(boundHeight - 2*h) + h;
}

int Fuel::update(std::list<Bullet*>& bullets, Player* player) {
  if(this->checkPlayerCollision(player)) return 1;
  if(this->checkBulletsCollision(bullets)) return 2;
  return 0;
}

void Fuel::render() {
  float y = *(this->y) + offsetY;
  
  glColor3f(0.87, 0.13, 0.22);
  glBegin(GL_POLYGON);
  glVertex2f(x  , y);
  glVertex2f(x  , y+h*4/17);
  glVertex2f(x+w, y+h*4/17);
  glVertex2f(x+w, y);
  glEnd();
  
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(x  , y+h*5/17);
  glVertex2f(x  , y+h*9/17);
  glVertex2f(x+w, y+h*9/17);
  glVertex2f(x+w, y+h*5/17);
  glEnd();
  
  glColor3f(0.87, 0.13, 0.22);
  glBegin(GL_POLYGON);
  glVertex2f(x  , y+h*10/17);
  glVertex2f(x  , y+h*14/17);
  glVertex2f(x+w, y+h*14/17);
  glVertex2f(x+w, y+h*10/17);
  glEnd();
  
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(x+w/4  , y+h*15/17);
  glVertex2f(x+w/4  , y+h*17/17);
  glVertex2f(x+w*3/4, y+h*17/17);
  glVertex2f(x+w*3/4, y+h*15/17);
  glEnd();
}

bool Fuel::checkPlayerCollision(Player* player) {
  return boxCollision(
    x, *y+offsetY, w, h,
    player->position.x, player->position.y, player->w, player->h
  );
}

bool Fuel::checkBulletsCollision(std::list<Bullet*>& bullets) {
  std::list<Bullet*>::iterator it = bullets.begin();
  while (it != bullets.end()){
    Bullet* bullet = *it;

    bool collision = boxCollision(
      x, *y+offsetY, w, h,
      bullet->position.x, bullet->position.y, bullet->size, bullet->size
    );

    if(collision){
      bullets.erase(it);
      return true;
    }

    ++it;
  }

  return false;
}



