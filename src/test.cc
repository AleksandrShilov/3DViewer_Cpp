#include <gtest/gtest.h>

#include <cmath>
#include <iomanip>

#include "model/model.h"

using namespace std;
my::data data_model = {
    {0.000000,  0.000000, 0.000000,  1.000000,  -1.000000, -1.000000, 1.000000,
     -1.000000, 1.000000, -1.000000, -1.000000, 1.000000,  -1.000000, -1.000000,
     -1.000000, 1.000000, 1.000000,  -1.000000, 1.000000,  1.000000,  1.000000,
     -1.000000, 1.000000, 1.000000,  -1.000000, 1.000000,  -1.000000},

    {2, 3, 3, 4, 4, 2, 8, 7, 7, 6, 6, 8, 5, 6, 6, 2, 2, 5, 6, 7, 7, 3, 3, 6,
     3, 7, 7, 8, 8, 3, 1, 4, 4, 8, 8, 1, 1, 2, 2, 4, 4, 1, 5, 8, 8, 6, 6, 5,
     1, 5, 5, 2, 2, 1, 2, 6, 6, 3, 3, 2, 4, 3, 3, 8, 8, 4, 5, 1, 1, 8, 8, 5}};

my::data data_model_move = {
    {0,  0, 0, 2,  -1, -1, 2, -1, 1, 0, -1, 1, 0, -1,
     -1, 2, 1, -1, 2,  1,  1, 0,  1, 1, 0,  1, -1},

    {2, 3, 3, 4, 4, 2, 8, 7, 7, 6, 6, 8, 5, 6, 6, 2, 2, 5, 6, 7, 7, 3, 3, 6,
     3, 7, 7, 8, 8, 3, 1, 4, 4, 8, 8, 1, 1, 2, 2, 4, 4, 1, 5, 8, 8, 6, 6, 5,
     1, 5, 5, 2, 2, 1, 2, 6, 6, 3, 3, 2, 4, 3, 3, 8, 8, 4, 5, 1, 1, 8, 8, 5}};

my::data data_model_scale = {
    {0,  0, 0, 2,  -2, -2, 2, -2, 2, -2, -2, 2, -2, -2,
     -2, 2, 2, -2, 2,  2,  2, -2, 2, 2,  -2, 2, -2},

    {2, 3, 3, 4, 4, 2, 8, 7, 7, 6, 6, 8, 5, 6, 6, 2, 2, 5, 6, 7, 7, 3, 3, 6,
     3, 7, 7, 8, 8, 3, 1, 4, 4, 8, 8, 1, 1, 2, 2, 4, 4, 1, 5, 8, 8, 6, 6, 5,
     1, 5, 5, 2, 2, 1, 2, 6, 6, 3, 3, 2, 4, 3, 3, 8, 8, 4, 5, 1, 1, 8, 8, 5}};

my::data data_model_rot_x = {
    {0.000000,  0.000000,  0.000000,  1.000000,  0.301169,  -1.381773, 1.000000,
     -1.381773, -0.301169, -1.000000, -1.381773, -0.301169, -1.000000, 0.301169,
     -1.381773, 1.000000,  1.381773,  0.301169,  1.000000,  -0.301169, 1.381773,
     -1.000000, -0.301169, 1.381773,  -1.000000, 1.381773,  0.301169},

    {2, 3, 3, 4, 4, 2, 8, 7, 7, 6, 6, 8, 5, 6, 6, 2, 2, 5, 6, 7, 7, 3, 3, 6,
     3, 7, 7, 8, 8, 3, 1, 4, 4, 8, 8, 1, 1, 2, 2, 4, 4, 1, 5, 8, 8, 6, 6, 5,
     1, 5, 5, 2, 2, 1, 2, 6, 6, 3, 3, 2, 4, 3, 3, 8, 8, 4, 5, 1, 1, 8, 8, 5}};

my::data data_model_rot_y = {
    {0.000000,  0.000000,  0.000000, -0.301169, -1.000000, -1.381773, 1.381773,
     -1.000000, -0.301169, 0.301169, -1.000000, 1.381773,  -1.381773, -1.000000,
     0.301169,  -0.301169, 1.000000, -1.381773, 1.381773,  1.000000,  -0.301169,
     0.301169,  1.000000,  1.381773, -1.381773, 1.000000,  0.301169},

    {2, 3, 3, 4, 4, 2, 8, 7, 7, 6, 6, 8, 5, 6, 6, 2, 2, 5, 6, 7, 7, 3, 3, 6,
     3, 7, 7, 8, 8, 3, 1, 4, 4, 8, 8, 1, 1, 2, 2, 4, 4, 1, 5, 8, 8, 6, 6, 5,
     1, 5, 5, 2, 2, 1, 2, 6, 6, 3, 3, 2, 4, 3, 3, 8, 8, 4, 5, 1, 1, 8, 8, 5}};

my::data data_model_rot_z = {
    {0.000000,  0.000000,  0.000000, 1.381773,  0.301169,  -1.000000, 1.381773,
     0.301169,  1.000000,  0.301169, -1.381773, 1.000000,  0.301169,  -1.381773,
     -1.000000, -0.301169, 1.381773, -1.000000, -0.301169, 1.381773,  1.000000,
     -1.381773, -0.301169, 1.000000, -1.381773, -0.301169, -1.000000},

    {2, 3, 3, 4, 4, 2, 8, 7, 7, 6, 6, 8, 5, 6, 6, 2, 2, 5, 6, 7, 7, 3, 3, 6,
     3, 7, 7, 8, 8, 3, 1, 4, 4, 8, 8, 1, 1, 2, 2, 4, 4, 1, 5, 8, 8, 6, 6, 5,
     1, 5, 5, 2, 2, 1, 2, 6, 6, 3, 3, 2, 4, 3, 3, 8, 8, 4, 5, 1, 1, 8, 8, 5}};

bool Equal(my::data const &data_temp) {
  for (size_t i = 0; i < data_model.vertex_coordinates.size(); ++i) {
    if (std::fabs(data_model.vertex_coordinates[i] -
                  data_temp.vertex_coordinates[i]) > 0.000001) {
      return false;
    }
  }
  return true;
};

bool EqualMove(my::data const &data_temp, my::data const &data_move) {
  for (size_t i = 0; i < data_move.vertex_coordinates.size(); ++i) {
    if (std::fabs(data_move.vertex_coordinates[i] -
                  data_temp.vertex_coordinates[i]) > 0.000001) {
      return false;
    }
  }
  return true;
};

bool EqualVert(my::data const &data_temp) {
  for (size_t i = 0; i < data_model.vertex_index.size(); ++i) {
    if (std::fabs(data_model.vertex_index[i] - data_temp.vertex_index[i]) >
        0.000001) {
      return false;
    }
  }
  return true;
};

// ************************ Test correct ************************

TEST(Correct, test_1) {
  std::shared_ptr<my::Singleton> model = my::Singleton::Instance();
  if (model->OpenFile("cube.obj")) {
    my::data temp = model->GetStruct();
    my::data temp_y = model->GetStruct();
    my::data temp_z = model->GetStruct();
    my::data temp_move = model->GetStruct();
    my::data temp_scale = model->GetStruct();
    model->RotateAxisX(temp.vertex_coordinates, 1.0);
    model->RotateAxisY(temp_y.vertex_coordinates, 1.0);
    model->RotateAxisZ(temp_z.vertex_coordinates, 1.0);
    model->MoveObject(temp_move.vertex_coordinates, 3, 1.0);
    model->ChangeScale(temp_scale.vertex_coordinates, 2.0);
    ASSERT_EQ(true, Equal(model->GetStruct()));
    ASSERT_EQ(true, EqualMove(temp, data_model_rot_x));
    ASSERT_EQ(true, EqualMove(temp_y, data_model_rot_y));
    ASSERT_EQ(true, EqualMove(temp_z, data_model_rot_z));
    ASSERT_EQ(true, EqualMove(temp_move, data_model_move));
    ASSERT_EQ(true, EqualMove(temp_scale, data_model_scale));
    ASSERT_EQ(true, EqualVert(model->GetStruct()));
    model->ClearStruct();
  }
}

TEST(Correct2, test_1) {
  std::shared_ptr<my::Singleton> model = my::Singleton::Instance();
  ASSERT_EQ(false, model->OpenFile("cub.obj"));
}

// ************************ Test incorrect ************************

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}