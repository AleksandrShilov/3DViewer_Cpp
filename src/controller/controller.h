#ifndef CPP4_3DVIEWER_V2_0_0_SRC_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_0_SRC_CONTROLLER_CONTROLLER_H_

#include "model/model.h"

namespace my {

class Controller {
 public:
  explicit Controller(std::shared_ptr<Singleton> m) : model_(m){};
  Controller(const Controller &other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(Controller &&other) = delete;
  ~Controller() = default;

 public:
  my::data GetStruct();
  bool OpenFile(const std::string &path);
  void MoveObject(std::vector<double> &coordinates, size_t elem,
                  double const &value);
  void ChangeScale(std::vector<double> &coordinates, double const &value);
  void RotateAxisX(std::vector<double> &coordinates, double const &value);
  void RotateAxisY(std::vector<double> &coordinates, double const &value);
  void RotateAxisZ(std::vector<double> &coordinates, double const &value);
  void ClearStruct();

 private:
  std::shared_ptr<Singleton> model_;
};

}  // namespace my

#endif  // CPP4_3DVIEWER_V2_0_0_SRC_CONTROLLER_CONTROLLER_H_
