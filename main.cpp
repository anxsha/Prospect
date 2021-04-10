#include <GL/glut.h>


int xRot = -135;
int zRot = -45;
double scale = 0.005;


void display();
void keybindings(int key, int, int);
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("OpenGl");
  glutInitWindowSize(1280, 720);
  glutDisplayFunc(display);
  glutSpecialFunc(keybindings);
  glutMainLoop();

  return 0;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glLoadIdentity();
  glRotated(xRot, 1.0, 0.0, 0.0);
  glRotated(zRot, 0.0, 0.0, 1.0);
  glScaled(scale, scale, scale);
  glFlush();
  glutSwapBuffers();
}

void keybindings(int key, int, int) {
  switch (key) {
    case GLUT_KEY_RIGHT:
      zRot = (zRot - 2) % 360;
      break;
    case GLUT_KEY_LEFT:
      zRot = (zRot + 2) % 360;
      break;
    case GLUT_KEY_UP:
      xRot = (xRot - 2) % 360;
      break;
    case GLUT_KEY_DOWN:
      xRot = (xRot + 2) % 360;
      break;
  }
  glutPostRedisplay();
}
