#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Player.h"

#include <iostream>

Player::Player(glm::vec2 pos) {
  this->position = pos;
}

void Player::update() {
  this->bulletSpawner->update();

  this->position.x += this->direction * this->speed;
}

void Player::render() {
  glColor3f(0.85, 0.7, 0.3);
  glBegin(GL_POLYGON);
  glVertex2f(this->position.x-20, this->position.y-20);
  glVertex2f(this->position.x-20, this->position.y+20);
  glVertex2f(this->position.x+20, this->position.y+20);
  glVertex2f(this->position.x+20, this->position.y-20);
  glEnd();

  this->bulletSpawner->render();
}

void Player::keyDown(unsigned char key, int x, int y) {
  if(key == 'a') this->direction = -1;
  if(key == 'd') this->direction = +1;
  if(key == ' ') this->bulletSpawner->spawnBullet(this->position);
}

void Player::keyUp(unsigned char key, int x, int y) {
  if(key == 'a' && this->direction == -1) this->direction = 0;
  if(key == 'd' && this->direction == +1) this->direction = 0;
}
