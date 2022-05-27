#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);
void draw_circle(float x, float y, float radius);

#define PI 3.14159265358979323846
#define W 800
#define H 800
#define R 100

int speed = 10;
int circle_1X = 200;
int circle_1Y = 200;
int circle_2X = 500;
int circle_2Y = 600;

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(W, H);

  glutInitWindowPosition(10, 300);

  glutCreateWindow("glut");

  glutKeyboardFunc(&keyboard);

  glutReshapeFunc(&resize);

  glutDisplayFunc(display);

  glutMainLoop();

  return EXIT_SUCCESS;
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case '\x1B':
      exit(EXIT_SUCCESS);
      break;
    case 'w':
      circle_1Y += speed;
      break;
    case 'a':
      circle_1X -= speed;
      break;
    case 's':
      circle_1Y -= speed;
      break;
    case 'd':
      circle_1X += speed;
      break;
  }

  if(circle_1X-R < 0)      circle_1X = R;
  else if(circle_1X+R > W) circle_1X = W - R;

  if(circle_1Y-R < 0)      circle_1Y = R;
  else if(circle_1Y+R > H) circle_1Y = H - R;

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

  float h2 = pow(circle_1X - circle_2X, 2) + pow(circle_1Y - circle_2Y, 2);
  bool col = h2 <= pow(2*R, 2);

  if(col) glColor3f(0.4, 0.2, 0.7);
  else    glColor3f(0.9, 0.2, 0.3);
  draw_circle(circle_2X, circle_2Y, R);

  glColor3f(0.1, 0.7, 0.3);
  draw_circle(circle_1X, circle_1Y, R);

  glColor3f(0.9, 0.7, 0.8);
  glBegin(GL_LINES);
    glVertex2f(circle_1X, circle_1Y);
    glVertex2f(circle_2X, circle_2Y);
  glEnd();

  glutSwapBuffers();
}

void draw_circle(float x, float y, float radius) {
  glBegin(GL_POLYGON);
  for (float r = 0; r < 2*PI; r += 0.001) {
    glVertex2f(x + cos(r)*radius, y + sin(r)*radius);
  }
  glEnd();
}

