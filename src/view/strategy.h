#ifndef CPP4_3DVIEWER_V2_0_0_SRC_VIEW_STRATEGY_H_
#define CPP4_3DVIEWER_V2_0_0_SRC_VIEW_STRATEGY_H_

#include "cmath"

namespace my {

class Strategy {
 public:
  virtual float Execute() = 0;
};

class ProjectionCentral : public Strategy {
 public:
  float Execute() override { return -10; }
};

class ProjectionParallel : public Strategy {
 public:
  float Execute() override {
    float fov = 60.0 * M_PI / 180;
    return 3 / (2 * tan(fov / 2));
  }
};

}  // namespace my

#endif  // CPP4_3DVIEWER_V2_0_0_SRC_VIEW_STRATEGY_H_
