#include "controller.h"

namespace my {

data Controller::GetStruct() { return model_->GetStruct(); }

bool Controller::OpenFile(const std::string &path) {
  return model_->OpenFile(path);
}

void Controller::MoveObject(std::vector<double> &coordinates, size_t elem,
                            const double &value) {
  model_->MoveObject(coordinates, elem, value);
}

void Controller::ChangeScale(std::vector<double> &coordinates,
                             const double &value) {
  model_->ChangeScale(coordinates, value);
}

void Controller::RotateAxisX(std::vector<double> &coordinates,
                             const double &value) {
  model_->RotateAxisX(coordinates, value);
}

void Controller::RotateAxisY(std::vector<double> &coordinates,
                             const double &value) {
  model_->RotateAxisY(coordinates, value);
}

void Controller::RotateAxisZ(std::vector<double> &coordinates,
                             const double &value) {
  model_->RotateAxisZ(coordinates, value);
}

void Controller::ClearStruct() { model_->ClearStruct(); }

}  // namespace my
