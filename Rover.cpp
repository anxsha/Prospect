#include "Rover.h"
#include "Cylinder.h"
#include <GL/glut.h>

void Rover::Draw() {
  glColor3f(0.3, 0.3, 0.4);

  Cylinder::Draw(0.0f, -20.0f, 0.0f, 4.5f, 10.0f, 100);
  Cylinder::Draw(30.0f, -20.0f, 0.0f, 4.5f, 10.0f, 100);
  Cylinder::Draw(60.0f, -20.0f, 0.0f, 4.5f, 10.0f, 100);

  Cylinder::Draw(0.0f, -20.0f, 30.0f, 4.5f, 10.0f, 100);
  Cylinder::Draw(30.0f, -20.0f, 30.0f, 4.5f, 10.0f, 100);
  Cylinder::Draw(60.0f, -20.0f, 30.0f, 4.5f, 10.0f, 100);

  Cylinder::Draw(0.0f, -20.0f, 0.0f, 30.0f, 2.0f, 100);
  Cylinder::Draw(30.0f, -20.0f, 0.0f, 30.0f, 2.0f, 100);
  Cylinder::Draw(60.0f, -20.0f, 0.0f, 30.0f, 2.0f, 100);
}
