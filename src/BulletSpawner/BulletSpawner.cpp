#include "BulletSpawner.h"
#include "../SoundController/SoundController.cpp"
#include <iostream>

BulletSpawner::BulletSpawner() {}

void BulletSpawner::update() {
  this->bullets.remove_if([](Bullet* bullet) {
    return !bullet->update();
  });

  if(this->bulletCooldown > 0.0f) this->bulletCooldown--;
}

void BulletSpawner::render() {
  for (auto const& bullet : this->bullets)
    bullet->render(); 
}

void BulletSpawner::spawnBullet(glm::vec2 position) {
  if(this->bulletCooldown <= 0.0f){
    Bullet* newBullet = new Bullet(position);
    this->bullets.push_back(newBullet);
    this->bulletCooldown = 10.0f;

    SoundController::play("shot");
  }
}

std::list<Bullet*>& BulletSpawner::getBullets() {
  return this->bullets;
}
