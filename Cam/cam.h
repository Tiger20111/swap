#ifndef CAM_H
#define CAM_H

#include <QWidget>
#include <QCamera>

namespace Ui {
  class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::Widget *ui;
};

#endif // CAM_H
