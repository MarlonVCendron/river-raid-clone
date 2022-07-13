#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Player.h"

Player::Player(glm::vec2 pos) {
  this->position = pos;
  this->w = 40;
  this->h = 40;
}

void Player::reset() {
  this->position = glm::vec2(glutGet(GLUT_WINDOW_WIDTH)/2 - 20, 100.0f);
}

void Player::update() {
  this->bulletSpawner->update();

  this->position.x += this->direction * this->speed;
}

void Player::render() {
  glColor3f(0.85, 0.7, 0.3);
  glBegin(GL_POLYGON);
  glVertex2f(this->position.x, this->position.y);
  glVertex2f(this->position.x, this->position.y + this->h);
  glVertex2f(this->position.x + this->w, this->position.y + this->h);
  glVertex2f(this->position.x + this->w, this->position.y);
  glEnd();

  this->bulletSpawner->render();
}

void Player::keyDown(unsigned char key, int x, int y) {
  if(key == 'a') this->direction = -1;
  if(key == 'd') this->direction = +1;
  if(key == ' ') this->bulletSpawner->spawnBullet(this->position + this->w / 2.0f);
}

void Player::keyUp(unsigned char key, int x, int y) {
  if(key == 'a' && this->direction == -1) this->direction = 0;
  if(key == 'd' && this->direction == +1) this->direction = 0;
}

std::list<Bullet*> Player::getBullets() {
  return this->bulletSpawner->getBullets();
}
