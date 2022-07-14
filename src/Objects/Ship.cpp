#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Ship.h"
#include "../Utils/checkCollision.h"
#include "../Utils/RandomNumber.h"

Ship::Ship(float boundX1, float boundX2, float* y, float boundHeight, float speed) {
  this->x = boundX1+(boundX2-boundX1)/2;
  this->y = y;
  this->boundX1 = boundX1;
  this->boundX2 = boundX2;
  this->speed = speed;
  this->offsetY = randomFloat(boundHeight - 2*h) + h;
}

int Ship::update(std::list<Bullet*>& bullets, Player* player) {
  this->x += speed;
  if(x < boundX1 + 50) speed = abs(speed);
  if(x+w > boundX2 - 50) speed = -abs(speed);

  if(this->checkPlayerCollision(player)) return 1;
  if(this->checkBulletsCollision(bullets)) return 2;
  return 0;
}

void Ship::render() {
  float y = *(this->y) + offsetY;
  
  // Fundo laranja
  glColor3f(0.68, 0.29, 0.04);
  glBegin(GL_POLYGON);
  glVertex2f(x+w*2/8, y);
  glVertex2f(x+w*1/8, y + h*1/8);
  glVertex2f(x+w*7/8, y + h*1/8);
  glVertex2f(x+w*6/8, y);
  glEnd();

  // Fundo preto
  glColor3f(0.05, 0.1, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(x+w*1/8, y + h*1/8);
  glVertex2f(x, y + h*4/8);
  glVertex2f(x+w, y + h*4/8);
  glVertex2f(x+w*7/8, y + h*1/8);
  glEnd();
  
  // Topo
  glColor3f(0.3, 0.2, 0.5);
  glBegin(GL_POLYGON);
  glVertex2f(x+w*1/8, y + h*4/8);
  glVertex2f(x+w*1/8, y + h*4/8);
  glVertex2f(x+w*3/8, y + h);
  glVertex2f(x+w*5/8, y + h);
  glVertex2f(x+w*5/8, y + h*4/8);
  glEnd();
}

bool Ship::checkPlayerCollision(Player* player) {
  return boxCollision(
    x, *y+offsetY, w, h,
    player->position.x, player->position.y, player->w, player->h
  );
}

bool Ship::checkBulletsCollision(std::list<Bullet*>& bullets) {
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



