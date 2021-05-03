#pragma once
#include "OBJ_Loader.h"
#include <vector>
#include <string>

class ObjModel {
 public:
  ObjModel(const std::string filename, const std::vector<float> color,
           const std::vector<float> coords, const float scale);
  void Draw();

 private:
  const std::vector<float> color_;
  const std::vector<float> coords_;
  const float scale_;
  objl::Loader loader_;
};
