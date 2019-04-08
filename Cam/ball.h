#ifndef BALL_H
#define BALL_H

#include <QGraphicsScene>
#include <QWidget>
#include <cmath>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QTextStream>
#include <QTimeLine>
#include <qfile.h>

class Ball {
  public:
    Ball();
    void runAnimation();
  private:
    QTimeLine *runTimer();

    QGraphicsScene *scene;
    QString inputFile;
    QString outputFile;
    std::pair<double, double> (*pointFunc1)(double);
};

#endif // BALL_H
