#ifndef FACE_MATCH_H
#define FACE_MATCH_H

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
#include <QFile>

namespace Ui {
class Face_match;
}

class Face_match : public QDialog
{
    Q_OBJECT

public:
    explicit Face_match(const QString name,const QString gender,const QString age,const QString id,const QString phone,QWidget* parent=nullptr);
    ~Face_match();

private slots:
    void on_pushButton_clicked();
    void updateFrame();
    void drawFaceRectangles(cv::Mat &frame);


private:
    Ui::Face_match *ui;
    cv::VideoCapture capture;
    cv::Mat frame;
    QTimer * frameTimer;
    cv::CascadeClassifier faceCascade;
    bool isCameraOpen=false;
    bool hasCapturedFace=false;
    dlib::frontal_face_detector detector;
    dlib::shape_predictor predictor;

    QString mname;
    QString mgender;
    QString mage;
    QString mid;
    QString mphone;

};

#endif // FACE_MATCH_H
