#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "Heli.h"
#include "../Utils/checkCollision.h"
#include "../Utils/RandomNumber.h"

Heli::Heli(float boundX1, float boundX2, float* y, float boundHeight, float speed) {
  this->x = boundX1+randomFloat(boundX2-boundX1-100);
  this->y = y;
  this->boundX1 = boundX1;
  this->boundX2 = boundX2;
  this->speed = rand()%2==0 ? speed : -speed;
  this->offsetY = randomFloat(boundHeight - 2*h) + h;
  this->counter = 0;
  this->animationFrame = false;
}

int Heli::update(std::list<Bullet*>& bullets, Player* player) {
  this->x += speed;
  if(x < boundX1 + 50) speed = abs(speed);
  if(x+w > boundX2 - 50) speed = -abs(speed);

  if(this->checkPlayerCollision(player)) return 1;
  if(this->checkBulletsCollision(bullets)) return 2;
  return 0;
}

void Heli::render() {
  float y = *(this->y) + offsetY;
  
  // Coisinho
  glColor3f(0.06, 0.02, 0.04);
  glBegin(GL_POLYGON);
  glVertex2f(x+w*1/8, y);
  glVertex2f(x+w*1/8, y+h*1/8);
  glVertex2f(x+w*4/8, y+h*1/8);
  glVertex2f(x+w*4/8, y);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(x+w*2/8, y+h*1/8);
  glVertex2f(x+w*2/8, y+h*2/8);
  glVertex2f(x+w*3/8, y+h*2/8);
  glVertex2f(x+w*3/8, y+h*1/8);
  glEnd();
  
  // Corpo
  glBegin(GL_POLYGON);
  glVertex2f(x, y+h*2/8);
  glVertex2f(x, y+h*6/8);
  glVertex2f(x+w*5/8, y+h*6/8);
  glVertex2f(x+w*5/8, y+h*2/8);
  glEnd();
  
  // Cauda
  glBegin(GL_POLYGON);
  glVertex2f(x+w*5/8, y+h*4/8);
  glVertex2f(x+w*5/8, y+h*5/8);
  glVertex2f(x+w, y+h*5/8);
  glVertex2f(x+w*7/8, y+h*4/8);
  glVertex2f(x+w, y+h*5/8);
  glEnd();

  // Vidro
  glColor3f(0.63, 0.6, 0.9);
  glBegin(GL_POLYGON);
  glVertex2f(x, y+h*4/8);
  glVertex2f(x, y+h*6/8);
  glVertex2f(x+w*2/8, y+h*6/8);
  glVertex2f(x+w*2/8, y+h*4/8);
  glEnd();

  float bw = h/8;
  if(animationFrame){
    glColor3f(0.95, 0.9, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y+h*6/8);
    glVertex2f(x-bw, y+h*7/8-bw);
    glVertex2f(x+w*5/8, y+h*7/8);
    glVertex2f(x+w*5/8+bw, y+h*6/8+bw);
    glEnd();
  }else{
    glColor3f(0.95, 0.9, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x-bw, y+h*6/8+bw);
    glVertex2f(x, y+h*7/8);
    glVertex2f(x+w*5/8+bw, y+h*7/8-bw);
    glVertex2f(x+w*5/8, y+h*6/8);
    glEnd();
  }
  
  if (counter % 4 == 0){
    animationFrame = !animationFrame;
  }
  if(counter == 10000) counter = 0;
  
  counter++;
}

bool Heli::checkPlayerCollision(Player* player) {
  return boxCollision(
    x, *y+offsetY, w, h,
    player->position.x, player->position.y, player->w, player->h
  );
}

bool Heli::checkBulletsCollision(std::list<Bullet*>& bullets) {
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



