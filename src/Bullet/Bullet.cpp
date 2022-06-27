#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Bullet.h"

#include <iostream>

Bullet::Bullet(glm::vec2 pos) {
  position = pos;
}

bool Bullet::update() {
  this->position.y += this->speed;
  if(this->position.y > glutGet(GLUT_WINDOW_HEIGHT)) return false;
  return true;
}

void Bullet::render() {
  glColor3f(0.75, 0.6, 0.3);
  glBegin(GL_POLYGON);
  glVertex2f(this->position.x-5, this->position.y-5);
  glVertex2f(this->position.x-5, this->position.y+5);
  glVertex2f(this->position.x+5, this->position.y+5);
  glVertex2f(this->position.x+5, this->position.y-5);
  glEnd();
}

