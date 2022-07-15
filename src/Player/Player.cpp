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
  this->position = glm::vec2(glutGet(GLUT_WINDOW_WIDTH)/2 - 20, 120.0f);
  this->fuel = initialFuel;
}

void Player::update() {
  fuel--;

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

  this->renderFuel();
  this->bulletSpawner->render();
}

void Player::renderFuel() {
  float w = 300.0, h = 80.0;
  float p = 10.0;
  float x = glutGet(GLUT_WINDOW_WIDTH)/2.0 - w/2.0;
  float innerW = w - 2*p;

  glColor3f(0.08, 0.07, 0.03);
  glBegin(GL_POLYGON);
  glVertex2f(x, 0);
  glVertex2f(x, h);
  glVertex2f(x+w, h);
  glVertex2f(x+w, 0);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINE_STRIP);
  glVertex2f(x+p, p);
  glVertex2f(x+p, h-p);
  glVertex2f(x+w-p, h-p);
  glVertex2f(x+w-p, p);
  glVertex2f(x+p, p);
  glEnd();

  glBegin(GL_LINES);
  glVertex2f(x+p+innerW*1/4, p);
  glVertex2f(x+p+innerW*1/4, 2*p);
  glVertex2f(x+p+innerW*2/4, p);
  glVertex2f(x+p+innerW*2/4, 2*p);
  glVertex2f(x+p+innerW*3/4, p);
  glVertex2f(x+p+innerW*3/4, 2*p);
  glEnd();

  float fuelPercentage = fuel*1.0 / initialFuel;
  glLineWidth(4.0);
  glColor3f(0.87, 0.13, 0.22);
  glBegin(GL_LINES);
  glVertex2f(x+p+innerW*fuelPercentage, 0);
  glVertex2f(x+p+innerW*fuelPercentage, 4*p);
  glEnd();
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

std::list<Bullet*>& Player::getBullets() {
  return this->bulletSpawner->bullets;
}

void Player::fillTank() {
  fuel+=5;
}


