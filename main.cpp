#include <GL/glut.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include "ObjModel.h"
#include "Rover.h"
#include "Ball.h"
#include "Cylinder.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

auto key_states = std::vector<bool>(256);

int x_rot = 0;
int y_rot = 0;
std::vector<std::unique_ptr<ObjModel>> env_objects;
std::vector<unsigned int> textures;
std::vector<std::string> img_names{"light_rock.jpg", "surface.jpg", "wood.jpeg",
                                   "tree.jpg",       "wood.jpeg",   "tree.jpg",
                                   "container.jpg"};

std::vector<std::vector<float>> goals = {{30.0f, 50.0f},
                                         {20.0f, 125.0f},
                                         {-65.0f, 170.0f},
                                         {0.0, 30.0},
                                         {20.0, -60.0}};
auto time_results = std::vector<std::string>(4);
int cur_goal = 0;
int cur_result = 0;
bool game_on = false;
float game_time = 0;

auto rover = Rover();

constexpr int BALL_INDEX = 0;
constexpr int GOALS_NUM = 5;

void load_textures() {
  textures = std::vector<unsigned int>(env_objects.size(), 0);
  int x;
  int y;
  int n;
  for (int i = 0; i < env_objects.size(); ++i) {
    glGenTextures(1, &textures.at(i));
    glBindTexture(GL_TEXTURE_2D, textures.at(i));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char* data = stbi_load(img_names.at(i).c_str(), &x, &y, &n, 4);
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }
}

void load_env_objects() {
  env_objects.push_back(std::make_unique<Ball>(
      Ball("rock.obj", std::vector<float>{0.4f, 0.4f, 0.4f},
           std::vector<float>{30.0f, 4.7f, 12.0f}, 6)));
  env_objects.push_back(std::make_unique<ObjModel>(
      ObjModel("surface.obj", std::vector<float>{1.0f, 0.8f, 0.8f},
               std::vector<float>{0.0f, -0.8f, 100.0f}, 20)));
  env_objects.push_back(std::make_unique<ObjModel>(
      ObjModel("trunk.obj", std::vector<float>{1.0f, 1.0f, 1.0f},
               std::vector<float>{-40.0f, 0.0f, 20.0f}, 7)));
  env_objects.push_back(std::make_unique<ObjModel>(
      ObjModel("tree.obj", std::vector<float>{0.2f, 0.5f, 0.2f},
               std::vector<float>{-40.0f, 19.0f, 20.0f}, 7)));
  env_objects.push_back(std::make_unique<ObjModel>(
      ObjModel("trunk.obj", std::vector<float>{1.0f, 1.0f, 1.0f},
               std::vector<float>{-50.0f, 0.0f, 90.0f}, 7)));
  env_objects.push_back(std::make_unique<ObjModel>(
      ObjModel("tree.obj", std::vector<float>{0.1f, 0.4f, 0.1f},
               std::vector<float>{-50.0f, 13.0f, 90.0f}, 7)));
  env_objects.push_back(std::make_unique<ObjModel>(
      ObjModel("buildings.obj", std::vector<float>{0.8f, 0.8f, 0.8f},
               std::vector<float>{30.0f, -0.8f, 80.0f}, 7)));
}

void DrawResults() {
  char results[4][20];
  strcpy_s(results[0], time_results.at(0).c_str());
  strcpy_s(results[1], time_results.at(1).c_str());
  strcpy_s(results[2], time_results.at(2).c_str());
  strcpy_s(results[3], time_results.at(3).c_str());

  glPushMatrix();
  glTranslatef(44.5, 35, 71.5);
  glRotatef(180, 0.0, 1.0, 0.0);
  glScalef(0.04, 0.04, 0.04);
  glColor3f(1, 1, 1);
  for (int line = 0; line < 4; ++line) {
    int len = strlen(results[line]);
    glPushMatrix();

    glTranslatef(-(len * 37), -(line * 200), 0.0);
    for (int i = 0; i < len; i++) {
      glColor3f(1, 1, 1.0);
      glutStrokeCharacter(GLUT_STROKE_ROMAN, results[line][i]);
    }
    glPopMatrix();
  }
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glLoadIdentity();
  glScalef(0.8, 0.8, 0.8);
  glRotated(x_rot, 1.0, 0.0, 0.0);
  glRotated(y_rot, 0.0, 1.0, 0.0);

  gluLookAt(rover.XPos() * 0.15 * 0.8 + 5, 20, rover.ZPos() * 0.15 * 0.8 - 10,
            rover.XPos() * 0.15 * 0.8+10, -15, rover.ZPos() * 0.15 * 0.8+10, 0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  int i = 0;
  for (auto&& obj : env_objects) {
    glBindTexture(GL_TEXTURE_2D, textures.at(i));
    obj->Draw();
    ++i;
  }

  glDisable(GL_TEXTURE_2D);

  DrawResults();

  if (game_on) {
    glColor3f(1.0f, 0.84f, 0.0f);
    Cylinder::Draw(goals.at(cur_goal).at(0), 0.0f, goals.at(cur_goal).at(1),
                   6.0f, 5.0f);
  }

  rover.Draw();

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glFlush();
  glutSwapBuffers();
}

void init_size() {
  float coord_range = 100.0f;
  int width = 1600;
  int height = 900;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-coord_range * width / height, coord_range * width / height,
          -coord_range, coord_range, -coord_range, coord_range);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void spec_key_down(int key, int x, int y) {
  switch (key) {
    /*case GLUT_KEY_RIGHT:
      y_rot = (y_rot - 2) % 360;
      break;
    case GLUT_KEY_LEFT:
      y_rot = (y_rot + 2) % 360;
      break;
    case GLUT_KEY_UP:
      x_rot = (x_rot - 2) % 360;
      break;
    case GLUT_KEY_DOWN:
      x_rot = (x_rot + 2) % 360;
      break;*/
    case GLUT_KEY_F1:
      game_on = true;
      break;
  }
  glutPostRedisplay();
}

void key_down(unsigned char key, int x, int y) { key_states.at(key) = true; }

void key_up(unsigned char key, int x, int y) { key_states.at(key) = false; }

void update(int val) {
  rover.UpdatePos(key_states, env_objects.at(BALL_INDEX)->getPos(),
                  env_objects.at(BALL_INDEX)->getRadius());
  glutPostRedisplay();
  glutTimerFunc(50, update, 0);
}

void game_state_update(int val) {
  if (game_on) {
    game_time += 0.1;
    if (rover.CheckCollision(goals.at(cur_goal).at(0), goals.at(cur_goal).at(1),
                             6.5f, rover.XPos(), rover.ZPos())) {
      ++cur_goal;
      if (cur_goal == GOALS_NUM) {
        game_on = false;
        std::stringstream str;
        if (game_time < 100.0f) {
          str << std::fixed << std::setprecision(3) << game_time;
          time_results.at(cur_result) = str.str();
          ++cur_result;
          cur_result %= 4;
        }
        game_time = 0;
        cur_goal = 0;
      }
    }
  }
  glutPostRedisplay();
  glutTimerFunc(100, game_state_update, 0);
}

void resize(int width, int height) { glutReshapeWindow(1600, 900); }

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Prospect");
  glutInitWindowSize(1600, 900);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutSpecialFunc(spec_key_down);
  glutKeyboardFunc(key_down);
  glutKeyboardUpFunc(key_up);
  glutTimerFunc(50, update, 0);
  glutTimerFunc(100, game_state_update, 0);

  init_size();

  load_env_objects();
  load_textures();

  glutMainLoop();

  return 0;
}
