#include "Rectangle.h"
#include <GL/glut.h>

void Rectangle::Draw(float x1, float length, float y1, float height, float z1, float depth) {
  if (!depth) {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1 + height, z1);
    glVertex3f(x1 + length, y1, z1);
    glVertex3f(x1 + length, y1 + height, z1);
    glEnd();
  } else {
    if (!height) {
      glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(x1, y1, z1);
      glVertex3f(x1, y1, z1 + depth);
      glVertex3f(x1 + length, y1, z1);
      glVertex3f(x1 + length, y1, z1 + depth);
      glEnd();
    } else {
      if (!length) {
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1 + height, z1);
        glVertex3f(x1, y1, z1 + depth);
        glVertex3f(x1, y1 + height, z1 + depth);
        glEnd();
      }
    }
  }
}
