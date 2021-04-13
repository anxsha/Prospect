#include "Rover.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Rectangle.h"
#include <GL/glut.h>
#include <cmath>

void Rover::Draw() {
  constexpr float ORIGIN_Y = -20.0f;
  constexpr float ROVER_WIDTH = 60.0f;
  constexpr float ROVER_LENGTH = 80.0f;

  glPushMatrix();

  // Zmniejszenie i obrót
  glScalef(0.8f, 0.8f, 0.8f);
  glRotatef(90, 0.0, 1.0, 0.0);

  // £¹czenia kó³
  glColor3f(0.3, 0.3, 0.4);
  Cylinder::Draw(0.0f, ORIGIN_Y, 4.0f, ROVER_WIDTH - 4.0f, 2.0f);
  Cylinder::Draw(ROVER_LENGTH / 2.0f, ORIGIN_Y, 4.0f, ROVER_WIDTH - 4.0f, 2.0f);
  Cylinder::Draw(ROVER_LENGTH, ORIGIN_Y, 4.0f, ROVER_WIDTH - 4.0f, 2.0f);

  // £¹czenie œrodkowe na dole
  glPushMatrix();
  glRotatef(90, 0.0, 1.0, 0.0);
  Cylinder::Draw(-32.25f, ORIGIN_Y, 0.0f, 80.0f, 2.0f);
  glPopMatrix();

  // £¹czenia do platformy
  glPushMatrix();
  glTranslatef(0.0f, ORIGIN_Y, 4.5f);
  glRotatef(360 - 60, 1.0, 0.0, 0.0);
  glRotatef(45, 0.0, 1.0, 0.0);
  glTranslatef(0.0f, -ORIGIN_Y, -4.5f);
  Cylinder::Draw(0.0f, ORIGIN_Y, 4.5f, 52.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, ORIGIN_Y, ROVER_WIDTH);
  glRotatef(240, 1.0, 0.0, 0.0);
  glRotatef(45, 0.0, 1.0, 0.0);
  glTranslatef(0.0f, -ORIGIN_Y, -ROVER_WIDTH);
  Cylinder::Draw(0.0f, ORIGIN_Y, ROVER_WIDTH, 52.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ROVER_LENGTH / 2, ORIGIN_Y, 4.5f);
  glRotatef(360 - 60, 1.0, 0.0, 0.0);
  glTranslatef(-(ROVER_LENGTH / 2), -ORIGIN_Y, -4.5f);
  Cylinder::Draw(ROVER_LENGTH / 2, ORIGIN_Y, 4.5f, 35.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ROVER_LENGTH / 2, ORIGIN_Y, ROVER_WIDTH);
  glRotatef(240, 1.0, 0.0, 0.0);
  glTranslatef(-(ROVER_LENGTH / 2), -ORIGIN_Y, -ROVER_WIDTH);
  Cylinder::Draw(ROVER_LENGTH / 2, ORIGIN_Y, ROVER_WIDTH, 35.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ROVER_LENGTH, ORIGIN_Y, 4.5f);
  glRotatef(120, 1.0, 0.0, 0.0);
  glRotatef(235, 0.0, 1.0, 0.0);
  glTranslatef(-(ROVER_LENGTH), -ORIGIN_Y, -4.5f);
  Cylinder::Draw(ROVER_LENGTH, ORIGIN_Y, 4.5f, 58.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(ROVER_LENGTH, ORIGIN_Y, ROVER_WIDTH);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(235, 0.0, 1.0, 0.0);
  glTranslatef(-(ROVER_LENGTH), -ORIGIN_Y, -ROVER_WIDTH);
  Cylinder::Draw(ROVER_LENGTH, ORIGIN_Y, ROVER_WIDTH, 58.0f, 2.0f);
  glPopMatrix();

  // Platforma
  glColor3f(0.69f, 0.77f, 0.87f);
  Cuboid::Draw(0.0f, ROVER_LENGTH, ORIGIN_Y + 40.0f, 5.0f, 5.0f, 55.0f);

  // Skrzynia pod platform¹
  glColor3f(0.27f, 0.283f, 0.298f);
  Cuboid::Draw(12.0f, 30.0f, ORIGIN_Y + 25.0f, 15.0f, 15.0f, 35.0f);

  // Antena
  // S³up
  glColor3f(0.3, 0.3, 0.35);
  glPushMatrix();
  glTranslatef(15.0f, ORIGIN_Y + 40.0f + 5.0f, ROVER_WIDTH / 2 - 5.0f);
  glRotatef(270, 1.0f, 0.0f, 0.0f);
  glTranslatef(-15.0f, -(ORIGIN_Y + 40.0f + 5.0f), -(ROVER_WIDTH / 2 - 5.0f));
  Cylinder::Draw(15.0f, ORIGIN_Y + 40.0f + 5.0f, ROVER_WIDTH / 2 - 5.0f, 25.0f, 1.5f);
  glPopMatrix();
  // Odbiornik
  glColor3f(0.8, 0.8, 0.85);
  glPushMatrix();
  glTranslatef(15.0f, ORIGIN_Y + 40.0f + 5.0f + 25.0f, ROVER_WIDTH / 2 - 5.0f);
  glRotatef(270, 1.0f, 0.0f, 0.0f);
  glTranslatef(-15.0f, -(ORIGIN_Y + 40.0f + 5.0f + 25.0f), -(ROVER_WIDTH / 2 - 5.0f));
  Cylinder::Draw(15.0f, ORIGIN_Y + 40.0f + 5.0f + 25.0f, ROVER_WIDTH / 2 - 5.0f, 1.0f, 10.0f);
  glPopMatrix();

  // Czujniki
  glColor3f(0.8f, 0.9f, 0.85f);
  Cylinder::Draw(20.0f, ORIGIN_Y + 25.0f + 5.0f, 15.0f, -1.5f, 2.5f);
  Cylinder::Draw(30.0f, ORIGIN_Y + 25.0f + 5.0f, 15.0f, -1.5f, 2.5f);
  Cylinder::Draw(20.0f, ORIGIN_Y + 25.0f + 5.0f, 50.0f, 1.5f, 2.5f);
  Cylinder::Draw(30.0f, ORIGIN_Y + 25.0f + 5.0f, 50.0f, 1.5f, 2.5f);
  glColor3f(0.1f, 0.1f, 0.1f);
  Cylinder::Draw(20.0f, ORIGIN_Y + 25.0f + 5.0f, 15.0f, -2.5f, 0.5f);
  Cylinder::Draw(30.0f, ORIGIN_Y + 25.0f + 5.0f, 15.0f, -2.5f, 0.5f);
  Cylinder::Draw(20.0f, ORIGIN_Y + 25.0f + 5.0f, 50.0f, 2.5f, 0.5f);
  Cylinder::Draw(30.0f, ORIGIN_Y + 25.0f + 5.0f, 50.0f, 2.5f, 0.5f);

  // Jedna strona kó³
  glColor3f(0.3, 0.3, 0.3);
  Cylinder::Draw(0.0f, ORIGIN_Y, 0.0f, 4.5f, 10.0f);
  Cylinder::Draw(ROVER_LENGTH / 2, ORIGIN_Y, 0.0f, 4.5f, 10.0f);
  Cylinder::Draw(ROVER_LENGTH, ORIGIN_Y, 0.0f, 4.5f, 10.0f);
  // Druga strona kó³
  Cylinder::Draw(0.0f, ORIGIN_Y, 60.0f, 4.5f, 10.0f);
  Cylinder::Draw(ROVER_LENGTH / 2, ORIGIN_Y, 60.0f, 4.5f, 10.0f);
  Cylinder::Draw(ROVER_LENGTH, ORIGIN_Y, 60.0f, 4.5f, 10.0f);

  glPopMatrix();
}
