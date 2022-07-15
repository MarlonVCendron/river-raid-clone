#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Bridge.h"
#include "../Utils/checkCollision.h"
#include "../Utils/RandomNumber.h"

Bridge::Bridge(float* y, float boundHeight) {
  this->x = 0;
  this->y = y;
  this->offsetY = randomFloat(boundHeight - 2*h) + h;
}

int Bridge::update(std::list<Bullet*>& bullets, Player* player) {
  if(this->checkPlayerCollision(player)) return 1;
  if(this->checkBulletsCollision(bullets)) bulletCount++;
  if(bulletCount >= 6) return 2;
  return 0;
}

void Bridge::render() {
  float y = *(this->y) + offsetY;
  float w = glutGet(GLUT_WINDOW_WIDTH);
  
  glColor3f(0.07, 0.13, 0.12);
  glBegin(GL_POLYGON);
  glVertex2f(x  , y);
  glVertex2f(x  , y+h);
  glVertex2f(x+w, y+h);
  glVertex2f(x+w, y);
  glEnd();

  float coisow = 80.0, coisoh = 15.0;
  for (float ix = coisow/2; ix<w; ix+=coisow*2) {
    glColor3f(0.87, 0.73, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(ix  , y+h/2-coisoh/2);
    glVertex2f(ix  , y+h/2+coisoh/2);
    glVertex2f(ix+coisow, y+h/2+coisoh/2);
    glVertex2f(ix+coisow, y+h/2-coisoh/2);
    glEnd();
  }
 }

bool Bridge::checkPlayerCollision(Player* player) {
  return player->position.y+player->h >= *y+offsetY;
}

bool Bridge::checkBulletsCollision(std::list<Bullet*>& bullets) {
  float w = glutGet(GLUT_WINDOW_WIDTH);

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


