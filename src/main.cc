#include <QApplication>

#include "controller/controller.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  std::shared_ptr<my::Singleton> model = my::Singleton::Instance();
  my::Controller controller(model);
  my::MainWindow w;
  w.SetController(&controller);
  w.show();
  return a.exec();
}
