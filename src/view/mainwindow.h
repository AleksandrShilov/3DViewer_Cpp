#ifndef CPP4_3DVIEWER_V2_0_0_SRC_VIEW_MAINWINDOW_H_
#define CPP4_3DVIEWER_V2_0_0_SRC_VIEW_MAINWINDOW_H_

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QToolTip>

#include "QtCore/qdatetime.h"
#include "command.h"
#include "controller/controller.h"
#include "qtgifimage/src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace my {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  MainWindow(const MainWindow &other) = delete;
  MainWindow &operator=(const MainWindow &other) = delete;
  MainWindow(MainWindow &&other) = delete;
  MainWindow &operator=(MainWindow &&other) = delete;
  ~MainWindow();

 public:
  void OpenFile();
  void SetController(my::Controller *c);

 private slots:
  void on_pushButton_rendering_clicked();
  void on_pushButton_open_f_clicked();
  void on_doubleSpinBox_x_valueChanged(double arg1);
  void on_doubleSpinBox_y_valueChanged(double arg1);
  void on_doubleSpinBox_z_valueChanged(double arg1);
  void on_doubleSpinBox_mashtab_valueChanged(double arg1);
  void on_doubleSpinBox_vertex_size_valueChanged(double arg1);
  void on_doubleSpinBox_edge_size_valueChanged(double arg1);
  void on_comboBox_edge_type_activated(const QString &arg1);
  void on_comboBox_vertex_type_activated(const QString &arg1);
  void on_comboBox_proection_activated(const QString &arg1);
  void on_pushButton_save_clicked();
  void on_pushButton_gif_clicked();
  void record_gif();
  void on_pushButton_save_settings_clicked();
  void on_pushButton_download_settings_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_color_edge_clicked();
  void on_pushButton_background_color_clicked();
  void on_pushButton_vertex_color_clicked();
  void on_doubleSpinBox_move_x_valueChanged(double arg1);
  void on_doubleSpinBox_move_y_valueChanged(double arg1);
  void on_doubleSpinBox_move_z_valueChanged(double arg1);
  void on_comboBox_viewtype_activated(const QString &arg1);
  void on_doubleSpinBox_change_r_valueChanged(double arg1);
  void on_doubleSpinBox_change_g_valueChanged(double arg1);
  void on_doubleSpinBox_change_b_valueChanged(double arg1);
  void on_doubleSpinBox_change_light_x_valueChanged(double arg1);
  void on_doubleSpinBox_change_light_y_valueChanged(double arg1);
  void on_doubleSpinBox_change_light_z_valueChanged(double arg1);

 private:
  QString GetPath();

 private:
  my::Controller *controller_;
  Ui::MainWindow *ui_;
  QString *path_gif_;
  QTimer *timer_;
  int timer_score_;
  QGifImage *gif_;
  QString filename_;
};

}  // namespace my

#endif  // CPP4_3DVIEWER_V2_0_0_SRC_VIEW_MAINWINDOW_H_
