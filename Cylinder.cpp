#include "Cylinder.h"
#include "Disc.h"

#include <GL/glut.h>
#include <cmath>

constexpr float PI = 3.14159265;

void Cylinder::Draw(float x, float y, float z, float height, float radius,
                    int precision) {
  Disc::Draw(x, y, z, radius, precision);
  Disc::Draw(x, y, z + height, radius, precision);

  glBegin(GL_TRIANGLE_STRIP);
  for (int i = 0; i < precision; ++i) {
    glVertex3f(x + radius * cos(PI * 2 * i / precision),
               y + radius * sin(PI * 2 * i / precision), z);
    glVertex3f(x + radius * cos(PI * 2 * i / precision),
               y + radius * sin(PI * 2 * i / precision), z + height);

    glVertex3f(x + radius * cos(0), y + radius * sin(0), z);
    glVertex3f(x + radius * cos(0), y + radius * sin(0), z + height);
  }
  glEnd();
}
