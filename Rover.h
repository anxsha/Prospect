#pragma once
class Rover {
 public:
  void Draw();
  Rover();
  void Accelerate();
  void Brake();
  void UpdatePos();
  void TurnRight();
  void TurnLeft();
 private:
  float origin_y;
  float origin_x;
  float origin_z;
  float speed;
  float wheel_rot;
};
