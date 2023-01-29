#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),
      colors_({{0, 255, 0}, {255, 0, 0}, {0, 0, 0, 1}}),
      point_size_(0),
      rots_({0, 0, 0}),
      flag_start_(0),
      types_({0, 0, 0, 0}),
      line_size_(0),
      coors_({0, 0, 0}),
      scale_(0),
      heap_height_(0),
      dif_{1.0, 1.0, 1.0, 1.0},
      lpos_{0.0, 0.0, 1.0, 1.0},
      amb_{0.0, 0.0, 0.0, 1.0} {}

Widget::~Widget() {}

void Widget::SetObjectValue(const my::data &object_value) {
  object_value_ = object_value;
}

my::data &Widget::GetObjectValue() { return object_value_; }

void Widget::SetVertColor(QColor const &q) { colors_.vert_color_ = q; }

QColor Widget::GetVertColor() const { return colors_.vert_color_; }

void Widget::SetLineColor(QColor const &q) { colors_.line_color_ = q; }

QColor Widget::GetLineColor() const { return colors_.line_color_; }

void Widget::SetBkgrColor(const QColor &q) { colors_.bkgr_color_ = q; }

QColor Widget::GetBkgrColor() const { return colors_.bkgr_color_; }

void Widget::SetFlagStart(const int &flag_start) { flag_start_ = flag_start; }

int Widget::GetFlagStart() const { return flag_start_; }

void Widget::SetPointSize(const int &point_size) { point_size_ = point_size; }

int Widget::GetPointSize() const { return point_size_; }

void Widget::SetFlagLineType(const int &flag_line_type) {
  types_.flag_line_type_ = flag_line_type;
}

int Widget::GetFlagLineType() const { return types_.flag_line_type_; }

void Widget::SetViewType(int const &flag_view_type) {
  types_.flag_view_type_ = flag_view_type;
}

int Widget::GetViewType() const { return types_.flag_view_type_; }

void Widget::SetFlagPointType(const int &flag_point_type) {
  types_.flag_point_type_ = flag_point_type;
}

int Widget::GetFlagPointType() const { return types_.flag_point_type_; }

void Widget::SetFlagProjectionType(const int &flag_projection_type) {
  types_.flag_projection_type_ = flag_projection_type;
}

int Widget::GetFlagProjectionType() const {
  return types_.flag_projection_type_;
}

void Widget::SetLineSize(const float &line_size) { line_size_ = line_size; }

float Widget::GetLineSize() const { return line_size_; }

void Widget::SetScale(const int &scale) { scale_ = scale; }

int Widget::GetScale() const { return scale_; }

void Widget::SetXCoor(const int &x_coor) { coors_.x_coor_ = x_coor; }

int Widget::GetXCoor() const { return coors_.x_coor_; }

void Widget::SetYCoor(const int &y_coor) { coors_.y_coor_ = y_coor; }

int Widget::GetYCoor() const { return coors_.y_coor_; }

void Widget::SetZCoor(const int &z_coor) { coors_.z_coor_ = z_coor; }

int Widget::GetZCoor() const { return coors_.z_coor_; }

void Widget::SetR(const float &r_color) { dif_[0] = r_color; }

void Widget::SetG(const float &g_color) { dif_[1] = g_color; }

void Widget::SetB(const float &b_color) { dif_[2] = b_color; }

void Widget::SetXLight(const float &x_coor) { lpos_[0] = x_coor; }

void Widget::SetYLight(const float &y_coor) { lpos_[1] = y_coor; }

void Widget::SetZLight(const float &z_coor) { lpos_[2] = z_coor; }

void Widget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  SettingLight();
}

void Widget::SettingLight() {
  if (types_.flag_view_type_) {
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos_);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  } else {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
  }
}

void Widget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Widget::paintGL() {
  glClearColor(colors_.bkgr_color_.redF(), colors_.bkgr_color_.greenF(),
               colors_.bkgr_color_.blueF(), colors_.bkgr_color_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!flag_start_) return;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  SettingProjection();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0, 0, -heap_height_ * 3);
  glRotatef(rots_.x_rot_, 1, 0, 0);
  glRotatef(rots_.y_rot_, 0, 1, 0);

  TypeLines();
  TypePoints();
  SettingLight();
  Lighting();
  DrawModel();
}

void Widget::mousePressEvent(QMouseEvent *mo) { m_pos_ = mo->pos(); }

void Widget::mouseMoveEvent(QMouseEvent *mo) {
  rots_.x_rot_ = 1 / M_PI * (mo->pos().y() - m_pos_.y());
  rots_.y_rot_ = 1 / M_PI * (mo->pos().x() - m_pos_.x());
  update();
}

void Widget::SettingProjection() {
  if (types_.flag_projection_type_ == 0) {
    my::ProjectionCentral central;
    glOrtho(-3, 3, -3, 3, central.Execute(), 100);
  } else if (types_.flag_projection_type_ == 1) {
    my::ProjectionParallel parallel;
    heap_height_ = parallel.Execute();
    glFrustum(-3, 3, -3, 3, heap_height_, 100);
  }
}

void Widget::TypeLines() {
  glLineWidth(line_size_);
  if (types_.flag_line_type_ == 0) {
    glDisable(GL_LINE_STIPPLE);
  } else if (types_.flag_line_type_ == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(0, 0x00ff);
  }
}

void Widget::TypePoints() {
  glPointSize(point_size_);
  if (types_.flag_point_type_ == 0) {
    glDisable(GL_POINT_SMOOTH);
  } else if (types_.flag_point_type_ == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else if (types_.flag_point_type_ == 2) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void Widget::Lighting() {
  switch (types_.flag_view_type_) {
    case 1:
      glShadeModel(GL_FLAT);
      break;
    case 2:
      glShadeModel(GL_SMOOTH);
      break;
    default:
      glShadeModel(GL_SMOOTH);
      break;
  }
}

void Widget::DrawModel() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, object_value_.vertex_coordinates.data());
  glNormalPointer(GL_FLOAT, 0, object_value_.normal_coordinates.data());
  glColor3f(colors_.line_color_.redF(), colors_.line_color_.greenF(),
            colors_.line_color_.blueF());
  if (types_.flag_view_type_) {
    glDrawElements(GL_QUADS, object_value_.vertex_index.size(), GL_UNSIGNED_INT,
                   object_value_.vertex_index.data());
  } else {
    glDrawElements(GL_LINES, object_value_.vertex_index.size(), GL_UNSIGNED_INT,
                   object_value_.vertex_index.data());
  }
  if (types_.flag_point_type_) {
    glColor3f(colors_.vert_color_.redF(), colors_.vert_color_.greenF(),
              colors_.vert_color_.blueF());
    glDrawArrays(GL_POINTS, 1,
                 (object_value_.vertex_coordinates.size() - 3) / 3);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}
