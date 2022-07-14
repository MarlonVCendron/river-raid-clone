#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/fwd.hpp>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <cstdlib>
#include <ctime>

#include "Level/Level.cpp"

#define W 1200
#define H 900
#define MSPF 10

Player* player;
Level* level;

void keyDown(unsigned char key, int x, int y) {
  if(key == '\x1B'){
    exit(EXIT_SUCCESS);
  }

  player->keyDown(key, x, y);
  glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
  player->keyUp(key, x, y);
  glutPostRedisplay();
}

void resize(GLsizei w, GLsizei h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0f, W, 0.0f, H);
  glMatrixMode(GL_MODELVIEW);
}

void display() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0, 0.26, 0.82, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  level->render();

  glutSwapBuffers();
}

void animate(int value) {
  glutPostRedisplay();
  if(level->update())
    glutTimerFunc(MSPF, animate, 1);
}

int main(int argc, char **argv) {
  srand(static_cast<unsigned>(time(0)));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutInitWindowSize(W, H);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("glut");
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutTimerFunc(MSPF, animate, 1);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);

  player = new Player(glm::vec2(W/2 - 20, 100.0f));
  level = new Level(player);

  glutMainLoop();

  return EXIT_SUCCESS;
}
