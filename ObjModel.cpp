#include "ObjModel.h"
#include <GL/glut.h>

ObjModel::ObjModel(const std::string filename, const std::vector<float> color,
                   const std::vector<float> coords, const float scale)
    : color_(color), coords_(coords), scale_(scale) {
  loader_.LoadFile(filename);
}

void ObjModel::Draw() {
  glPushMatrix();
  glScalef(scale_, scale_, scale_);
  objl::Mesh mesh;
  for (auto& i_mesh : loader_.LoadedMeshes) {
    int n = 0;
    auto v1 = std::vector<float>(3);
    auto v2 = std::vector<float>(3);
    auto v3 = std::vector<float>(3);
    for (auto& j_mesh : i_mesh.Indices) {
      if (n == 0) {
        v1.at(0) = i_mesh.Vertices[j_mesh].Position.X;
        v1.at(1) = i_mesh.Vertices[j_mesh].Position.Y;
        v1.at(2) = i_mesh.Vertices[j_mesh].Position.Z;
      } else if (n == 1) {
        v2.at(0) = i_mesh.Vertices[j_mesh].Position.X;
        v2.at(1) = i_mesh.Vertices[j_mesh].Position.Y;
        v2.at(2) = i_mesh.Vertices[j_mesh].Position.Z;
      } else {
        v3.at(0) = i_mesh.Vertices[j_mesh].Position.X;
        v3.at(1) = i_mesh.Vertices[j_mesh].Position.Y;
        v3.at(2) = i_mesh.Vertices[j_mesh].Position.Z;
      }
      ++n;
      if (n == 3) {
        n = 0;
        glBegin(GL_TRIANGLES);
        glColor3f(color_.at(0), color_.at(1), color_.at(2));
        glTexCoord2d(0, 0);
        glVertex3f(coords_.at(0) / scale_ + v1.at(0),
                   coords_.at(1) / scale_ + v1.at(1),
                   coords_.at(2) / scale_ + v1.at(2));

        glTexCoord2d(0, 1);
        glVertex3f(coords_.at(0) / scale_ + v2.at(0),
                   coords_.at(1) / scale_ + v2.at(1),
                   coords_.at(2) / scale_ + v2.at(2));

        glTexCoord2d(1, 0);
        glVertex3f(coords_.at(0) / scale_ + v3.at(0),
                   coords_.at(1) / scale_ + v3.at(1),
                   coords_.at(2) / scale_ + v3.at(2));
        glEnd();
      }
    }
  }
  glPopMatrix();
}