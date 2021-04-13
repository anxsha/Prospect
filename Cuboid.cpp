#include "Cuboid.h"
#include "Rectangle.h"

void Cuboid::Draw(float x1, float length, float y1, float height, float z1,
                  float depth) {
  Rectangle::Draw(x1, length, y1, height, z1);
  Rectangle::Draw(x1, length, y1, height, z1 + depth);
  Rectangle::Draw(x1, length, y1, 0, z1, depth);
  Rectangle::Draw(x1, length, y1 + height, 0, z1, depth);
  Rectangle::Draw(x1, 0, y1, height, z1, depth);
  Rectangle::Draw(x1 + length, 0, y1, height, z1, depth);
}
