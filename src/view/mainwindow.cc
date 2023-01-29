#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace my {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  this->setFixedHeight(776);
  this->setFixedWidth(1015);
  path_gif_ = nullptr;
  timer_ = nullptr;
  timer_score_ = 0;
}

MainWindow::~MainWindow() {
  if (path_gif_) {
    delete path_gif_;
  }
  if (timer_) {
    delete timer_;
  }
  delete ui_;
}

void MainWindow::OpenFile() {
  filename_ = QFileDialog::getOpenFileName(this, "Выберите файл",
                                           QDir::homePath(), "*.obj");
  ui_->openGLWidget->SetFlagStart(1);
}

void MainWindow::SetController(Controller *c) { controller_ = c; }

void MainWindow::on_pushButton_rendering_clicked() {
  if (ui_->openGLWidget->GetFlagStart() == 1) {
    controller_->ClearStruct();
    char *filepath = filename_.toLocal8Bit().data();
    setlocale(LC_NUMERIC, "C");
    struct my::data objectValue2;
    if (!(controller_->OpenFile(filepath))) {
      QMessageBox::warning(this, "Error", "File is not open");
    }
    objectValue2 = controller_->GetStruct();
    QString scoreEdge =
        QString::number((objectValue2.vertex_index.size() / 2) / 3);
    QString scoreVertexes =
        QString::number((objectValue2.vertex_coordinates.size() - 3) / 3);

    ui_->label_edge->setText("Рёбер: " + scoreEdge);
    ui_->label_vertex->setText("Вершин: " + scoreVertexes);
    ui_->label_name_file->setText("Файл: " + QFileInfo(filename_).fileName());
    ui_->openGLWidget->SetObjectValue(objectValue2);
    ui_->openGLWidget->SetFlagStart(2);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_pushButton_open_f_clicked() {
  Start *start_open = new Start(ui_->openGLWidget);
  filename_ = QFileDialog::getOpenFileName(this, "Выберите файл",
                                           QDir::homePath(), "*.obj");
  start_open->Execute();
  delete start_open;
}

void MainWindow::on_doubleSpinBox_x_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    if (arg1 > this->ui_->openGLWidget->GetXCoor()) {
      controller_->RotateAxisX(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 0.1);
    } else {
      controller_->RotateAxisX(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, -0.1);
    }
    this->ui_->openGLWidget->SetXCoor(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_y_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    if (arg1 > this->ui_->openGLWidget->GetYCoor()) {
      controller_->RotateAxisY(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 0.1);
    } else {
      controller_->RotateAxisY(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, -0.1);
    }
    this->ui_->openGLWidget->SetYCoor(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_z_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    if (arg1 > this->ui_->openGLWidget->GetZCoor()) {
      controller_->RotateAxisZ(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 0.1);
    } else {
      controller_->RotateAxisZ(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, -0.1);
    }
    this->ui_->openGLWidget->SetZCoor(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_mashtab_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    if (arg1 > this->ui_->openGLWidget->GetScale()) {
      controller_->ChangeScale(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 1.5);
    } else {
      controller_->ChangeScale(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 0.75);
    }
    this->ui_->openGLWidget->SetScale(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_vertex_size_valueChanged(double arg1) {
  ui_->openGLWidget->SetPointSize(arg1);
  ui_->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_edge_size_valueChanged(double arg1) {
  ui_->openGLWidget->SetLineSize(arg1);
  ui_->openGLWidget->update();
}

void MainWindow::on_comboBox_edge_type_activated(const QString &arg1) {
  if (arg1 == "Пунктирная") {
    ui_->openGLWidget->SetFlagLineType(1);
  } else if (arg1 == "Сплошная") {
    ui_->openGLWidget->SetFlagLineType(0);
  }
  ui_->openGLWidget->update();
}

void MainWindow::on_comboBox_vertex_type_activated(const QString &arg1) {
  if (arg1 == "Отсутствует") {
    ui_->openGLWidget->SetFlagPointType(0);
  } else if (arg1 == "Круг") {
    ui_->openGLWidget->SetFlagPointType(1);
  } else if (arg1 == "Квадрат") {
    ui_->openGLWidget->SetFlagPointType(2);
  }
  ui_->openGLWidget->update();
}

void MainWindow::on_comboBox_proection_activated(const QString &arg1) {
  if (arg1 == "Параллельная") {
    ui_->openGLWidget->SetFlagProjectionType(0);
  } else if (arg1 == "Центральная") {
    ui_->openGLWidget->SetFlagProjectionType(1);
  }
  ui_->openGLWidget->update();
}

void MainWindow::on_pushButton_save_clicked() {
  if (ui_->radioButton_jpeg->isChecked()) {
    this->ui_->openGLWidget->grab().save(GetPath() + "/" + "screencast" +
                                         QTime::currentTime().toString() + "." +
                                         "jpeg");
  } else if (ui_->radioButton_bmp->isChecked()) {
    this->ui_->openGLWidget->grab().save(GetPath() + "/" + "screencast" +
                                         QTime::currentTime().toString() + "." +
                                         "bmp");
  }
}

QString MainWindow::GetPath() {
  return QFileDialog::getExistingDirectory(
      this->ui_->openGLWidget, tr("Choose files"), QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_pushButton_gif_clicked() {
  path_gif_ = new QString(GetPath());
  gif_ = new QGifImage();
  timer_score_ = 0;
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(record_gif()));
  timer_->start(100);
}

void MainWindow::record_gif() {
  ++timer_score_;
  gif_->addFrame(ui_->openGLWidget->grabFramebuffer(), 100);
  if (timer_score_ == 50) {
    timer_->stop();
    gif_->save(*path_gif_ + "/" + QDate::currentDate().toString() + " " +
               QTime::currentTime().toString() + ".gif");
    delete gif_;
  }
}

void MainWindow::on_pushButton_save_settings_clicked() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("settings");
  settings.setValue("projection_type",
                    ui_->openGLWidget->GetFlagProjectionType());
  settings.setValue("back_color", ui_->openGLWidget->GetBkgrColor());
  settings.setValue("vertexes_color", ui_->openGLWidget->GetVertColor());
  settings.setValue("point_type", ui_->openGLWidget->GetFlagPointType());
  settings.setValue("point_size", ui_->openGLWidget->GetPointSize());
  settings.setValue("line_color", ui_->openGLWidget->GetLineColor());
  settings.setValue("line_type_flag", ui_->openGLWidget->GetFlagLineType());
  settings.setValue("line_sizes", ui_->openGLWidget->GetLineSize());
  settings.setValue("value_scale", ui_->openGLWidget->GetScale());
  settings.setValue("view_type", ui_->openGLWidget->GetViewType());
  settings.endGroup();
}

void MainWindow::on_pushButton_download_settings_clicked() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("settings");
  int typeProjection = settings.value("projection_type").toInt();
  ui_->openGLWidget->SetFlagProjectionType(typeProjection);
  ui_->openGLWidget->SetBkgrColor(
      settings.value("back_color", QColor(Qt::black)).value<QColor>());
  ui_->openGLWidget->SetVertColor(
      settings.value("vertexes_color", QColor(Qt::black)).value<QColor>());
  int type_point = settings.value("point_type").toInt();
  ui_->openGLWidget->SetFlagPointType(type_point);
  int size_point = settings.value("point_size").toInt();
  ui_->openGLWidget->SetPointSize(size_point);
  ui_->openGLWidget->SetLineColor(
      settings.value("line_color", QColor(Qt::black)).value<QColor>());
  int line_type = settings.value("line_type_flag").toInt();
  ui_->openGLWidget->SetFlagLineType(line_type);
  float line_size = settings.value("line_sizes").toFloat();
  ui_->openGLWidget->SetLineSize(line_size);
  float scale_value = settings.value("value_scale").toFloat();
  ui_->openGLWidget->SetScale(scale_value);
  ui_->openGLWidget->update();
}

void MainWindow::on_pushButton_clear_clicked() {
  ui_->openGLWidget->SetFlagStart(0);
  ui_->comboBox_proection->setCurrentIndex(0);
  ui_->comboBox_edge_type->setCurrentIndex(0);
  ui_->comboBox_vertex_type->setCurrentIndex(0);
  ui_->comboBox_viewtype->setCurrentIndex(0);
  ui_->doubleSpinBox_edge_size->setValue(0.0);
  ui_->doubleSpinBox_vertex_size->setValue(0.0);
  ui_->doubleSpinBox_mashtab->setValue(0.0);
  ui_->doubleSpinBox_x->setValue(0.0);
  ui_->doubleSpinBox_y->setValue(0.0);
  ui_->doubleSpinBox_z->setValue(0.0);
  ui_->doubleSpinBox_move_x->setValue(0.0);
  ui_->doubleSpinBox_move_y->setValue(0.0);
  ui_->doubleSpinBox_move_z->setValue(0.0);
  ui_->radioButton_jpeg->setChecked(true);
  ui_->label_edge->setText("Рёбер:");
  ui_->label_vertex->setText("Вершин:");
  ui_->label_name_file->setText("Файл:");
  ui_->openGLWidget->SetVertColor({0, 255, 0});
  ui_->openGLWidget->SetLineColor({255, 0, 0});
  ui_->openGLWidget->SetBkgrColor({0, 0, 0, 0});
  ui_->openGLWidget->SetPointSize(2);
  ui_->openGLWidget->SetLineSize(1.1);
  ui_->openGLWidget->SetFlagLineType(0);
  ui_->openGLWidget->SetFlagPointType(0);
  ui_->openGLWidget->SetFlagProjectionType(0);
  controller_->ClearStruct();
  ui_->openGLWidget->update();
}

void MainWindow::on_pushButton_color_edge_clicked() {
  ui_->openGLWidget->SetLineColor(QColorDialog::getColor());
  ui_->openGLWidget->update();
}

void MainWindow::on_pushButton_background_color_clicked() {
  ui_->openGLWidget->SetBkgrColor(QColorDialog::getColor());
  ui_->openGLWidget->update();
}

void MainWindow::on_pushButton_vertex_color_clicked() {
  ui_->openGLWidget->SetVertColor(QColorDialog::getColor());
  ui_->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_move_x_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    if (arg1 > this->ui_->openGLWidget->GetXCoor()) {
      controller_->MoveObject(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 3, 0.1);
      this->ui_->openGLWidget->SetXCoor(arg1);
    } else {
      controller_->MoveObject(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 3,
          -0.1);
      this->ui_->openGLWidget->SetXCoor(arg1);
    }
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_move_y_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    if (arg1 > this->ui_->openGLWidget->GetYCoor()) {
      controller_->MoveObject(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 4, 0.1);
      this->ui_->openGLWidget->SetYCoor(arg1);
    } else {
      controller_->MoveObject(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 4,
          -0.1);
      this->ui_->openGLWidget->SetYCoor(arg1);
    }
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_move_z_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    if (arg1 > this->ui_->openGLWidget->GetZCoor()) {
      controller_->MoveObject(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 5, 0.1);
      this->ui_->openGLWidget->SetZCoor(arg1);
    } else {
      controller_->MoveObject(
          this->ui_->openGLWidget->GetObjectValue().vertex_coordinates, 5,
          -0.1);
      this->ui_->openGLWidget->SetZCoor(arg1);
    }
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_comboBox_viewtype_activated(const QString &arg1) {
  if (arg1 == "Каркасная модель") {
    ui_->openGLWidget->SetViewType(0);
  } else if (arg1 == "Плоское затенение") {
    ui_->openGLWidget->SetViewType(1);
  } else if (arg1 == "Мягкое затенение") {
    ui_->openGLWidget->SetViewType(2);
  }
  ui_->openGLWidget->update();
}

void MainWindow::on_doubleSpinBox_change_r_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    this->ui_->openGLWidget->SetR(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_change_g_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    this->ui_->openGLWidget->SetG(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_change_b_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    this->ui_->openGLWidget->SetB(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_change_light_x_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    this->ui_->openGLWidget->SetXLight(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_change_light_y_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    this->ui_->openGLWidget->SetYLight(arg1);
    ui_->openGLWidget->update();
  }
}

void MainWindow::on_doubleSpinBox_change_light_z_valueChanged(double arg1) {
  if (ui_->openGLWidget->GetFlagStart()) {
    this->ui_->openGLWidget->SetZLight(arg1);
    ui_->openGLWidget->update();
  }
}

}  // namespace my
