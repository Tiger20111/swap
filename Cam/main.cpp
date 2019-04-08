#include "cam.h"
#include <QApplication>
#include "ball.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Ball *ball = new Ball();
  ball->runAnimation();
  Widget w;
  w.show();

  return a.exec();
}
