#pragma once
#include <vector>
class Rover {
 public:
  void Draw();
  Rover();
  void Accelerate();
  void Brake();
  void UpdatePos(const std::vector<bool>& key_states,
                 const std::vector<float>& obstacle_coords, float radius);
  void TurnRight();
  void TurnLeft();
  bool CheckCollision(float obj_centre_x, float obj_centre_z, float radius, float new_x, float new_z);

 private:
  float origin_y;
  float origin_x;
  float origin_z;
  float speed;
  float wheel_rot;
  float rover_centre_x;
  float rover_centre_z;
  float wheel_turn;
};
