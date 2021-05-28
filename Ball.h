#pragma once
#include "ObjModel.h"
class Ball : public ObjModel {
 public:
  Ball(const std::string filename, const std::vector<float> color,
        std::vector<float> coords, const float scale);
  virtual void Draw() override;
  virtual float getRadius() override;

 private:
  float radius_;
};
