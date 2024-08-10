#ifndef FACECK_H
#define FACECK_H

#include <QDialog>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <QTimer>
#include <QMessageBox>
#include <QImage>
#include <fstream>
#include <vector>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <QDebug>
#include <opencv2/dnn.hpp>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>




namespace Ui {
class FaceCk;
}

class FaceCk : public QDialog
{
    Q_OBJECT

public:
    explicit FaceCk(QWidget *parent = nullptr);
    ~FaceCk();
    bool matchFaces(const QStringList &facefile, const QStringList &facecapt);

private slots:
    void on_pushButton_clicked();
    void updateFrame();
    void drawFaceRectangles(cv::Mat &frame);

private:
    Ui::FaceCk *ui;
    QTimer * frameTimer;
    cv::VideoCapture capture;
    cv::Mat frame;
    cv::CascadeClassifier faceCascade;
    bool isCameraOpen=false;
    bool hasCapturedFace=false;
    dlib::frontal_face_detector detector;
    dlib::shape_predictor predictor;
};

#endif // FACECK_H
