#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/fwd.hpp>
#include <stdlib.h>
#include <glm/glm.hpp>

#include "Player/Player.cpp"

#define W 800
#define H 800
#define MSPF 10

Player* player = new Player(glm::vec2(100.0f, 100.0f));

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


  glClearColor(0.13, 0.1, 0.12, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  player->render();

  glutSwapBuffers();
}

void animate(int value) {
  player->update();
  glutPostRedisplay();
  glutTimerFunc(MSPF, animate, 1);
}

int main(int argc, char **argv) {
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
  glutMainLoop();
  return EXIT_SUCCESS;
}
