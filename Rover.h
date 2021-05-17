#pragma once
#include <vector>
class Rover {
 public:
  void Draw();
  Rover();
  void Accelerate();
  void Brake();
  void UpdatePos(const std::vector<bool>& key_states);
  void TurnRight();
  void TurnLeft();
 private:
  float origin_y;
  float origin_x;
  float origin_z;
  float speed;
  float wheel_rot;
  float rover_centre_x;
  float rover_centre_z;
};
