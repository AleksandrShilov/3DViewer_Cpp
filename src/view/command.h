#ifndef CPP4_3DVIEWER_V2_0_0_SRC_VIEW_COMMAND_H_
#define CPP4_3DVIEWER_V2_0_0_SRC_VIEW_COMMAND_H_

#include "widget.h"

namespace my {

class Command {
 public:
  virtual void Execute() = 0;
};

class Start : public Command {
 public:
  explicit Start(Widget *w) : widget_(w) {}
  void Execute() override { widget_->SetFlagStart(1); }

 private:
  Widget *widget_;
};

}  // namespace my

#endif  // CPP4_3DVIEWER_V2_0_0_SRC_VIEW_COMMAND_H_
