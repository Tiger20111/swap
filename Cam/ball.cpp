#include "ball.h"
#include "myitem.h"

std::pair<double, double> NextPointCircle (double time) {
  std::pair<double, double> new_point(0, 0);
  new_point.first = 80 * sin(time);
  new_point.second = 80 * cos(time);
  return new_point;
}

std::pair<double, double> NextPointCos (std::pair<double, double> point) {
  std::pair<double, double> new_point(0, 0);
  new_point.first = point.first + 10;
  new_point.second = 80 * cos(point.first);
  return new_point;
}

std::pair<double, double> NextPointFunction(std::pair<double, double> (*funcPoint)(std::pair<double, double>), std::pair<double, double> point) {
  return (*funcPoint)(point);
}

void CircleMotion(QGraphicsItemAnimation *animation, std::pair<double, double> (*funcPoint)(double), const QString output) {
  std::pair<double, double>next_point(0, 0);

  QFile fileOut(output);
  QTextStream writeStream(&fileOut);
  if(!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  for (int i = 0; i < 30; ++i) {
    next_point = funcPoint((double)i);
    writeStream << next_point.first << " " << next_point.second << "\n";
    animation->setPosAt(i / 30.0, QPointF(next_point.first, next_point.second));
  }
  fileOut.close();
}

void CircleMotionFromFile(QGraphicsItemAnimation *animation, std::pair<double, double> (*funcPoint)(std::pair<double, double>), QString input) {
  std::pair<double, double>next_point(0, 0);
  QFile fileOut(input);
  QTextStream readStream(&fileOut);
  for (int i = 0; i < 26; ++i) {
      readStream >> next_point.first >> next_point.second;
      animation->setPosAt(i / 26.0, QPointF(next_point.first, next_point.second));
  }
}

void DrawBorder (QGraphicsScene *scene) {
  scene->setSceneRect(-10, -10, 300, 300);
  QPen mypen = QPen(Qt::red);

  QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
  QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
  QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
  QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

  scene ->addLine(TopLine, mypen);
  scene ->addLine(LeftLine, mypen);
  scene ->addLine(RightLine, mypen);
  scene ->addLine(BottomLine, mypen);

}


Ball::Ball() {
  outputFile = "C:/Users/Tiger20111/Documents/trajectory.txt";
  inputFile = "/home/tigtig/Inprac/Animation/Trajectory/in_ball_tajectory.txt";
  pointFunc1 = &NextPointCircle;

}

QTimeLine *Ball::runTimer() {
  QTimeLine *timer = new QTimeLine(20000);
  timer->setFrameRange(0, 100);
  timer->setUpdateInterval(25);
  return timer;
}



void Ball::runAnimation() {
  QGraphicsView *view;
  scene = new QGraphicsScene();
  view = new QGraphicsView (scene);

  DrawBorder(scene);

  QTimeLine* timer = runTimer();

  MyItem *item = new MyItem();
  QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
  animation->setItem(item);
  animation->setTimeLine(timer);

  CircleMotion(animation, pointFunc1, outputFile);

  scene->addItem(item);
  view->show();
  timer->start();
}


//std::pair<double, double> (*pointFunc)(std::pair<double, double>) = NULL;
//pointFunc = &NextPointCos;
//CircleMotionFromFile(animation, pointFunc, inputFile);
