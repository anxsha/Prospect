#include <GL/glut.h>
#include "Renderer.h"


int x_rot = 0;
int y_rot = 0;



void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glLoadIdentity();
  glRotated(x_rot, 1.0, 0.0, 0.0);
  glRotated(y_rot, 0.0, 1.0, 0.0);

  Renderer::Render();

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glFlush();
  glutSwapBuffers();
}

void init_size() {
  float coord_range = 100.0f;
  int width = 1280;
  int height = 720;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-coord_range * width / height, coord_range * width / height,
          -coord_range, coord_range, -coord_range, coord_range);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keybindings(int key, int, int) {
  switch (key) {
    case GLUT_KEY_RIGHT:
      y_rot = (y_rot - 2) % 360;
      break;
    case GLUT_KEY_LEFT:
      y_rot = (y_rot + 2) % 360;
      break;
    case GLUT_KEY_UP:
      x_rot = (x_rot - 2) % 360;
      break;
    case GLUT_KEY_DOWN:
      x_rot = (x_rot + 2) % 360;
      break;
  }
  glutPostRedisplay();
}

void resize(int width, int height) { glutReshapeWindow(1280, 720); }

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("OpenGl");
  glutInitWindowSize(1280, 720);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutSpecialFunc(keybindings);

  init_size();

  glutMainLoop();

  return 0;
}
