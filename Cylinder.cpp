#include "Cylinder.h"
#include "Disc.h"

#include <GL/glut.h>
#include <cmath>

constexpr float PI = 3.14159265;
constexpr int TRIANGLE_PRECISION = 100;

void Cylinder::Draw(float x, float y, float z, float height, float radius) {
  Disc::Draw(x, y, z, radius);
  Disc::Draw(x, y, z + height, radius);

  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i < TRIANGLE_PRECISION; ++i) {
    glVertex3f(x + radius * cos(PI * 2 * i / TRIANGLE_PRECISION),
               y + radius * sin(PI * 2 * i / TRIANGLE_PRECISION), z);
    glVertex3f(x + radius * cos(PI * 2 * i / TRIANGLE_PRECISION),
               y + radius * sin(PI * 2 * i / TRIANGLE_PRECISION), z + height);

    glVertex3f(x + radius * cos(0), y + radius * sin(0), z);
    glVertex3f(x + radius * cos(0), y + radius * sin(0), z + height);
  }
  glEnd();
}
