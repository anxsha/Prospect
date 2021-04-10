#include "Disc.h"
#include <GL/glut.h>
#include <cmath>

constexpr float PI = 3.14159265;

void Disc::Draw(float x, float y, float z, float radius, int precision) {
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(x, y, z);
  for (int i = 0; i < precision; ++i) {
    glVertex3f( x + radius * cos(PI * 2 * i / precision),
               y + radius * sin(PI * 2 * i / precision), z);
  }
  glVertex3f(x + radius * cos(0), y + radius * sin(0), z);
  glEnd();
}
