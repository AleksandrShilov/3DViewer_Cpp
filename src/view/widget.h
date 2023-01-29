#ifndef CPP4_3DVIEWER_V2_0_0_SRC_VIEW_WIDGET_H_
#define CPP4_3DVIEWER_V2_0_0_SRC_VIEW_WIDGET_H_

#include <QFile>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>

#include "model/model.h"
#include "strategy.h"

struct Coors {
  float x_coor_;
  float y_coor_;
  float z_coor_;
};

struct Rots {
  float x_rot_;
  float y_rot_;
  float z_rot_;
};

struct Colors {
  QColor vert_color_;
  QColor line_color_;
  QColor bkgr_color_;
};

struct Types {
  int flag_line_type_;
  int flag_point_type_;
  int flag_projection_type_;
  int flag_view_type_;
};

class Widget : public QOpenGLWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  Widget(const Widget &other) = delete;
  Widget &operator=(const Widget &other) = delete;
  Widget(Widget &&other) = delete;
  Widget &operator=(Widget &&other) = delete;
  ~Widget();

 public:
  void SetObjectValue(my::data const &object_value);
  my::data &GetObjectValue();
  void SetVertColor(QColor const &q);
  QColor GetVertColor() const;
  void SetLineColor(QColor const &q);
  QColor GetLineColor() const;
  void SetBkgrColor(QColor const &q);
  QColor GetBkgrColor() const;
  void SetFlagStart(int const &flag_start);
  int GetFlagStart() const;
  void SetPointSize(int const &point_size);
  int GetPointSize() const;
  void SetFlagLineType(int const &flag_line_type);
  int GetFlagLineType() const;
  void SetViewType(int const &flag_view_type);
  int GetViewType() const;
  void SetFlagPointType(int const &flag_point_type);
  int GetFlagPointType() const;
  void SetFlagProjectionType(int const &flag_projection_type);
  int GetFlagProjectionType() const;
  void SetLineSize(float const &line_size);
  float GetLineSize() const;
  void SetScale(int const &scale_);
  int GetScale() const;
  void SetXCoor(int const &x_coor);
  int GetXCoor() const;
  void SetYCoor(int const &y_coor);
  int GetYCoor() const;
  void SetZCoor(int const &z_coor);
  int GetZCoor() const;
  void SetR(const float &r_color);
  void SetG(const float &g_color);
  void SetB(const float &b_color);
  void SetXLight(const float &x_coor);
  void SetYLight(const float &y_coor);
  void SetZLight(const float &z_coor);

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *mouse) override;
  void mouseMoveEvent(QMouseEvent *mouse) override;

  void SettingProjection();
  void SettingLight();
  void TypeLines();
  void TypePoints();
  void Lighting();
  void DrawModel();

 private:
  struct my::data object_value_;
  Colors colors_;
  Types types_;
  int flag_start_;
  int point_size_;
  float line_size_;
  float scale_;
  Coors coors_;
  Rots rots_;
  float heap_height_;
  QPoint m_pos_;
  QTimer timer_;
  float dif_[4];
  float lpos_[4];
  float amb_[4];
};

#endif  // CPP4_3DVIEWER_V2_0_0_SRC_VIEW_WIDGET_H_
