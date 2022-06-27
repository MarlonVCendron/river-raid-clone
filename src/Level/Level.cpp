#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Level.h"

#include <iostream>

bool Level::tryAddTile() {
  float height = 200.0f;
  LevelTile* lastTile = this->tiles.back();
  const float y = lastTile == NULL ? 0 : lastTile->getTopY();
  if(y > glutGet(GLUT_WINDOW_HEIGHT)) return false;

  this->tiles.push_back(new LevelTile(y, this->speed, height));
  return true;
}

Level::Level() {
  bool done = false;
  while(!done){
    done = !this->tryAddTile();
  }
}

void Level::update() {
  this->tiles.remove_if([=](LevelTile* tile) {
    this->tryAddTile();
    return !tile->update();
  });
}

void Level::render() {
  for (auto const& tile : this->tiles)
    tile->render(); 
}

