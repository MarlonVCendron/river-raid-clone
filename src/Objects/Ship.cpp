#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Ship.h"
#include "../Utils/checkCollision.h"
#include "../Utils/RandomNumber.cpp"

Ship::Ship(float boundX1, float boundX2, float* y, float boundHeight, float speed) {
  this->x = boundX1+(boundX2-boundX1)/2;
  this->y = y;
  this->boundX1 = boundX1;
  this->boundX2 = boundX2;
  this->speed = speed;
  this->offsetY = randomFloat(boundHeight - 2*h) + h;
}

bool Ship::update(std::list<Bullet*> bullets, Player* player) {
  this->x += speed;
  if(x < boundX1 + 50) speed = abs(speed);
  if(x+w > boundX2 - 50) speed = -abs(speed);

  this->checkPlayerCollision(player);
  return this->checkBulletsCollision(bullets);
}

void Ship::render() {
  glColor3f(0.3, 0.2, 0.5);
  glBegin(GL_POLYGON);
  glVertex2f(x, *y+offsetY);
  glVertex2f(x, *y+offsetY + h);
  glVertex2f(x + w, *y+offsetY + h);
  glVertex2f(x + w, *y+offsetY);
  glEnd();
}

bool Ship::checkPlayerCollision(Player* player) {
  return boxCollision(
    x, *y+offsetY, x+w, *y+offsetY+h,
    player->position.x, player->position.y, player->w, player->h
  );
}


bool Ship::checkBulletsCollision(std::list<Bullet*> bullets) {
  bullets.remove_if([=](Bullet* bullet) {
    bool col = boxCollision(
      x, *y+offsetY, x+w, *y+offsetY+h,
      bullet->position.x, bullet->position.y, bullet->size, bullet->size
    );

    std::cout << col << '\n';
    return col;
  });
  return false;
}




