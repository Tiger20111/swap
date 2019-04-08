#include "cam.h"
#include "ui_cam.h"

#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaRecorder>
#include <QUrl>
#include <QCameraImageCapture>
#include <QLabel>


Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget) {
    ui->setupUi(this);

    QCamera *camera = new QCamera(QCameraInfo::availableCameras().at(0));
    connect(camera, SIGNAL( error (Q:Caera::Error)), this, SLOT( cameraError( QCamera:Error)));
    QCameraViewfinder *viewFinder = new QCameraViewfinder(this);

    auto viewfinder = new QCameraViewfinder;
    viewfinder->setMinimumSize( 50, 50 );
    camera->setViewfinder( viewfinder );
    camera->setCaptureMode( QCamera::CaptureStillImage );

    auto timerLabel = new QLabel;
    QString timerLabelTpl = "<p align=\"center\"><span style=\"font-size:50pt; font-weight:600; color:#FF0000;\">%1</span></p>";


    QMediaRecorder* recorder = new QMediaRecorder(camera);
    recorder->setOutputLocation(QUrl(QString("C:/hm/testvideo.mp4"))); // removed my name

    auto settings = recorder->videoSettings();
    settings.setResolution(640,480);
    settings.setQuality(QMultimedia::VeryHighQuality);
    settings.setFrameRate(30.0);

    recorder->setVideoSettings(settings);

    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->start();
    camera->searchAndLock();
    QCameraImageCapture* imageCapture = new QCameraImageCapture(camera);
    imageCapture->setCaptureDestination( QCameraImageCapture::CaptureToFile );
    recorder->record();
    recorder->startTimer(1000);

    for (int i = 0; i < 1000; i++) {

      }
    qDebug()<<recorder->state();
    qDebug()<<recorder->status();
    qDebug()<<recorder->error();
     qDebug()<<recorder->outputLocation();
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_pushButton_clicked()
{

}
