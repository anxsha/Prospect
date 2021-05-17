#include "Rover.h"
#include "Cylinder.h"
#include "Cuboid.h"
#include "Rectangle.h"
#include <GL/glut.h>
#include <cmath>

constexpr float PI = 3.14159265;
constexpr float ROVER_WIDTH = 60.0f;
constexpr float ROVER_LENGTH = 80.0f;
constexpr float SCALE = 0.15f;

Rover::Rover()
    : origin_y{0.0f},
      origin_x{-50.0f},
      origin_z{-20.0f},
      speed{0.0f},
      wheel_rot{0.0f},
      rover_centre_x{origin_x + ROVER_LENGTH / 2.0f},
      rover_centre_z{origin_z + ROVER_WIDTH / 2.0f + 2.25f} {};

void Rover::Accelerate() {
  if (speed < 600.0f) {
    speed += 5.0f;
  }
  if (speed < -50.0f) {
    speed += 15.0f;
  }
}

void Rover::Brake() {
  if (speed > -600.f) {
    speed -= 5.0f;
  }
  if (speed > 50.0f) {
    speed -= 15.0f;
  }
}

void Rover::TurnRight() {
  if (wheel_rot < 360) {
    wheel_rot += 5.0f;
  }
}

void Rover::TurnLeft() {
  if (wheel_rot > -360) {
    wheel_rot -= 5.0f;
  }
}

void Rover::UpdatePos(const std::vector<bool>& key_states) {
  // switch (key) {
  //  case 'w':
  //    rover.Accelerate();
  //    break;
  //  case 's':
  //    rover.Brake();
  //    break;
  //  case 'a':
  //    rover.TurnLeft();
  //    break;
  //  case 'd':
  //    rover.TurnRight();
  //    break;
  //}
  if (key_states.at('w')) {
    Accelerate();
  }
  if (key_states.at('s')) {
    Brake();
  }
  if (key_states.at('a')) {
    TurnLeft();
  }
  if (key_states.at('d')) {
    TurnRight();
  }
  if (speed > 4.0f || speed < -4.0f) {
    float dx = speed * 0.03f * cos(wheel_rot * PI / 180);
    float dz = speed * 0.03f * sin(-wheel_rot * PI / 180);
    origin_x -= dx;
    origin_z += dz;
    rover_centre_x = origin_x + ROVER_LENGTH / 2.0f;
    rover_centre_z = origin_z + ROVER_WIDTH / 2.0f + 2.25f;
  }
  if (speed > -2.0f && speed < 2.0f) {
    speed = 0.0f;
  } else if (speed > 2.0f) {
    speed -= 2.0f;
  } else if (speed < -2.0f) {
    speed += 2.0f;
  }
}

void Rover::Draw() {
  glPushMatrix();

  // Zmniejszenie
  glScalef(SCALE, SCALE, SCALE);

  glTranslatef(rover_centre_x, origin_y, rover_centre_z);
  glRotatef(-wheel_rot / 1.5, 0.0, 1, 0.0);
  glTranslatef(-rover_centre_x, -origin_y, -rover_centre_z);

  glColor3f(1, 0, 0);
  glPointSize(15);
  glBegin(GL_LINES);
  glVertex3f(rover_centre_x, 0, rover_centre_z);
  glVertex3f(rover_centre_x, 200, rover_centre_z);
  glEnd();

  // £¹czenia kó³
  glColor3f(0.3, 0.3, 0.4);
  Cylinder::Draw(origin_x, origin_y, origin_z + 4.0f, ROVER_WIDTH - 4.0f, 2.0f);
  Cylinder::Draw(origin_x + ROVER_LENGTH / 2.0f, origin_y, origin_z + 4.0f,
                 ROVER_WIDTH - 4.0f, 2.0f);
  Cylinder::Draw(origin_x + ROVER_LENGTH, origin_y, origin_z + 4.0f,
                 ROVER_WIDTH - 4.0f, 2.0f);

  // £¹czenie œrodkowe na dole
  glPushMatrix();
  glRotatef(90, 0.0, 1.0, 0.0);
  Cylinder::Draw(-(origin_z + (ROVER_WIDTH / 2) + (4.5 / 2)), origin_y,
                 origin_x, ROVER_LENGTH, 2.0f);
  glPopMatrix();

  // £¹czenia do platformy
  glPushMatrix();
  glTranslatef(origin_x, origin_y, origin_z + 4.5f);
  glRotatef(360 - 60, 1.0, 0.0, 0.0);
  glRotatef(45, 0.0, 1.0, 0.0);
  glTranslatef(-origin_x, -origin_y, -(origin_z + 4.5f));
  Cylinder::Draw(origin_x, origin_y, origin_z + 4.5f, 52.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(origin_x, origin_y, origin_z + ROVER_WIDTH);
  glRotatef(240, 1.0, 0.0, 0.0);
  glRotatef(45, 0.0, 1.0, 0.0);
  glTranslatef(-origin_x, -origin_y, -(origin_z + ROVER_WIDTH));
  Cylinder::Draw(origin_x, origin_y, origin_z + ROVER_WIDTH, 52.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(origin_x + ROVER_LENGTH / 2, origin_y, origin_z + 4.5f);
  glRotatef(360 - 60, 1.0, 0.0, 0.0);
  glTranslatef(-(origin_x + ROVER_LENGTH / 2), -origin_y, -(origin_z + 4.5f));
  Cylinder::Draw(origin_x + ROVER_LENGTH / 2, origin_y, origin_z + 4.5f, 35.0f,
                 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(origin_x + ROVER_LENGTH / 2, origin_y, origin_z + ROVER_WIDTH);
  glRotatef(240, 1.0, 0.0, 0.0);
  glTranslatef(-(origin_x + ROVER_LENGTH / 2), -origin_y,
               -(origin_z + ROVER_WIDTH));
  Cylinder::Draw(origin_x + ROVER_LENGTH / 2, origin_y, origin_z + ROVER_WIDTH,
                 35.0f, 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(origin_x + ROVER_LENGTH, origin_y, origin_z + 4.5f);
  glRotatef(120, 1.0, 0.0, 0.0);
  glRotatef(235, 0.0, 1.0, 0.0);
  glTranslatef(-(origin_x + ROVER_LENGTH), -origin_y, -(origin_z + 4.5f));
  Cylinder::Draw(origin_x + ROVER_LENGTH, origin_y, origin_z + 4.5f, 58.0f,
                 2.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(origin_x + ROVER_LENGTH, origin_y, origin_z + ROVER_WIDTH);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(235, 0.0, 1.0, 0.0);
  glTranslatef(-(origin_x + ROVER_LENGTH), -origin_y,
               -(origin_z + ROVER_WIDTH));
  Cylinder::Draw(origin_x + ROVER_LENGTH, origin_y, origin_z + ROVER_WIDTH,
                 58.0f, 2.0f);
  glPopMatrix();

  // Platforma
  glColor3f(0.69f, 0.77f, 0.87f);
  Cuboid::Draw(origin_x, ROVER_LENGTH, origin_y + 40.0f, 5.0f, origin_z + 5.0f,
               55.0f);

  // Skrzynia pod platform¹
  glColor3f(0.27f, 0.283f, 0.298f);
  Cuboid::Draw(origin_x + 12.0f, 30.0f, origin_y + 25.0f, 15.0f,
               origin_z + 15.0f, 35.0f);

  // Antena
  // S³up
  glColor3f(0.3, 0.3, 0.35);
  glPushMatrix();
  glTranslatef(15.0f, origin_y + 40.0f + 5.0f,
               origin_z + ROVER_WIDTH / 2 - 5.0f);
  glRotatef(270, 1.0f, 0.0f, 0.0f);
  glTranslatef(-15.0f, -(origin_y + 40.0f + 5.0f),
               -(origin_z + ROVER_WIDTH / 2 - 5.0f));
  Cylinder::Draw(origin_x + 15.0f, origin_y + 40.0f + 5.0f,
                 origin_z + ROVER_WIDTH / 2 - 5.0f, 25.0f, 1.5f);
  glPopMatrix();
  // Odbiornik
  glColor3f(0.8, 0.8, 0.85);
  glPushMatrix();
  glTranslatef(15.0f, origin_y + 40.0f + 5.0f + 25.0f,
               origin_z + ROVER_WIDTH / 2 - 5.0f);
  glRotatef(270, 1.0f, 0.0f, 0.0f);
  glTranslatef(-15.0f, -(origin_y + 40.0f + 5.0f + 25.0f),
               -(origin_z + ROVER_WIDTH / 2 - 5.0f));
  Cylinder::Draw(origin_x + 15.0f, origin_y + 40.0f + 5.0f + 25.0f,
                 origin_z + ROVER_WIDTH / 2 - 5.0f, 1.0f, 10.0f);
  glPopMatrix();

  // Czujniki
  glColor3f(0.8f, 0.9f, 0.85f);
  Cylinder::Draw(origin_x + 20.0f, origin_y + 25.0f + 5.0f, origin_z + 15.0f,
                 -1.5f, 2.5f);
  Cylinder::Draw(origin_x + 30.0f, origin_y + 25.0f + 5.0f, origin_z + 15.0f,
                 -1.5f, 2.5f);
  Cylinder::Draw(origin_x + 20.0f, origin_y + 25.0f + 5.0f, origin_z + 50.0f,
                 1.5f, 2.5f);
  Cylinder::Draw(origin_x + 30.0f, origin_y + 25.0f + 5.0f, origin_z + 50.0f,
                 1.5f, 2.5f);
  glColor3f(0.1f, 0.1f, 0.1f);
  Cylinder::Draw(origin_x + 20.0f, origin_y + 25.0f + 5.0f, origin_z + 15.0f,
                 -2.5f, 0.5f);
  Cylinder::Draw(origin_x + 30.0f, origin_y + 25.0f + 5.0f, origin_z + 15.0f,
                 -2.5f, 0.5f);
  Cylinder::Draw(origin_x + 20.0f, origin_y + 25.0f + 5.0f, origin_z + 50.0f,
                 2.5f, 0.5f);
  Cylinder::Draw(origin_x + 30.0f, origin_y + 25.0f + 5.0f, origin_z + 50.0f,
                 2.5f, 0.5f);

  // Jedna strona kó³
  glColor3f(0.5, 0.3, 0.3);
  glPushMatrix();
  glTranslatef(origin_x, origin_y, origin_z);
  glRotatef(-wheel_rot / 2, 0.0f, 1.0f, 0.0f);
  glTranslatef(-origin_x, -origin_y, -origin_z);
  Cylinder::Draw(origin_x, origin_y, origin_z, 4.5f, 10.0f);
  glPopMatrix();
  glColor3f(0.3, 0.3, 0.3);

  Cylinder::Draw(origin_x + ROVER_LENGTH / 2, origin_y, origin_z, 4.5f, 10.0f);

  glPushMatrix();
  glTranslatef(origin_x + ROVER_LENGTH, origin_y, origin_z);
  glRotatef(-wheel_rot / 3, 0.0f, 1.0f, 0.0f);
  glTranslatef(-(origin_x + ROVER_LENGTH), -origin_y, -origin_z);
  Cylinder::Draw(origin_x + ROVER_LENGTH, origin_y, origin_z, 4.5f, 10.0f);
  glPopMatrix();

  // Druga strona kó³
  glColor3f(0.5, 0.3, 0.3);
  glPushMatrix();
  glTranslatef(origin_x, origin_y, origin_z + 60);
  glRotatef(-wheel_rot / 2, 0.0f, 1.0f, 0.0f);
  glTranslatef(-origin_x, -origin_y, -(origin_z + 60));
  Cylinder::Draw(origin_x, origin_y, origin_z + 60.0f, 4.5f, 10.0f);
  glPopMatrix();
  glColor3f(0.3, 0.3, 0.3);

  Cylinder::Draw(origin_x + ROVER_LENGTH / 2, origin_y, origin_z + 60.0f, 4.5f,
                 10.0f);

  glPushMatrix();
  glTranslatef(origin_x + ROVER_LENGTH, origin_y, origin_z + ROVER_WIDTH);
  glRotatef(-wheel_rot / 3, 0.0f, 1.0f, 0.0f);
  glTranslatef(-(origin_x + ROVER_LENGTH), -origin_y,
               -(origin_z + ROVER_WIDTH));
  Cylinder::Draw(origin_x + ROVER_LENGTH, origin_y, origin_z + ROVER_WIDTH,
                 4.5f, 10.0f);
  glPopMatrix();

  glPopMatrix();
}
