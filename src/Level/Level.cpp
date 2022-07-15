#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include "Level.h"

bool Level::tryAddTile() {
  LevelTile* lastTile = this->tiles.back();
  const float y = lastTile == NULL ? 0 : lastTile->getTopY();
  if(y > glutGet(GLUT_WINDOW_HEIGHT)) return false;


  if(this->connector){
    float halfWidth = glutGet(GLUT_WINDOW_WIDTH) / 2.0;
    float x1 = randomFloat(halfWidth - 140) + 40;
    float x2 = randomFloat(halfWidth - 140) + halfWidth - 40;

    this->tiles.push_back(new LevelTile(y, &this->speed, x1, x2, this->prevX1, this->prevX2));
    this->prevX1 = x1;
    this->prevX2 = x2;
  } else {
    this->tiles.push_back(new LevelTile(y, &this->speed, this->prevX1, this->prevX2, this->prevX1, this->prevX2));
  }

  this->connector = !this->connector;
  return true;
}

Level::Level(Player* player) {
  //SoundController::play("music");
  this->player = player;
  prevX1 = 200;
  prevX2 = glutGet(GLUT_WINDOW_WIDTH) - 200;
  connector = false;

  bool doneAddingTiles = false;
  while(!doneAddingTiles){
    doneAddingTiles = !tryAddTile();
  }
}

void Level::update() {
  this->tiles.remove_if([=](LevelTile* tile) {
    this->tryAddTile();
    int tileStatus = tile->update(this->player->getBullets(), player);
    if(tileStatus == 2 && !restarting) this->endGame();
    return (tileStatus == 1);
  });

  if(restarting) return;

  int i = 0;
  for (auto const& tile : this->tiles) {
    if(tile->checkPlayerCollision(player)) {
      this->endGame();
      return;
    }

    if(++i >= 2) break; // Checar apenas dois primeiros
  }

  this->player->update();
  if(player->fuel < 0) this->endGame();
}

void Level::render() {
  for (std::list<LevelTile*>::reverse_iterator tile = tiles.rbegin(); tile != tiles.rend(); ++tile)
    (*tile)->render();

  if(!restarting) this->player->render();
}

void Level::threadReset() {
  std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));

  prevX1 = 200;
  prevX2 = glutGet(GLUT_WINDOW_WIDTH) - 200;
  connector = false;

  tiles.clear();
  bool doneAddingTiles = false;
  while(!doneAddingTiles){
    doneAddingTiles = !tryAddTile();
  }

  speed = 5.0;
  restarting = false;
  player->reset();
}

void Level::endGame() {
  SoundController::play("explosion");
  speed = 0;
  player->speed = 0;
  restarting = true;

  std::thread t( [this] { this->threadReset(); } );
  t.detach();
}

