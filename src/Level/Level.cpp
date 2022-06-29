#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Level.h"

#include <iostream>

bool Level::tryAddTile() {
  LevelTile* lastTile = this->tiles.back();
  const float y = lastTile == NULL ? 0 : lastTile->getTopY();
  if(y > glutGet(GLUT_WINDOW_HEIGHT)) return false;

  this->tiles.push_back(new LevelTile(y, &this->speed));
  return true;
}

Level::Level(Player* player) {
  this->player = player;

  bool doneAddingTiles = false;
  while(!doneAddingTiles){
    doneAddingTiles = !this->tryAddTile();
  }
}

bool Level::update() {
  std::list<Bullet*> bullets = this->player->getBullets();

  this->tiles.remove_if([=](LevelTile* tile) {
    this->tryAddTile();
    return !tile->update(bullets);
  });

  int i = 0;
  for (auto const& tile : this->tiles) {
    if(tile->checkPlayerCollision(player))
      return false;
      //this->speed = 0;

    if(++i >= 2) break; // Checar apenas dois primeiros
  }

  this->player->update();
  return true;
}

void Level::render() {
  for (auto const& tile : this->tiles)
    tile->render(); 

  this->player->render();
}

