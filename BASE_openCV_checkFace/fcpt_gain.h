#ifndef FCPT_GAIN_H
#define FCPT_GAIN_H

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

namespace Ui {
class fcpt_Gain;
}

class fcpt_Gain : public QDialog
{
    Q_OBJECT

public:
    //explicit fcpt_Gain(QWidget *parent = nullptr);
    explicit fcpt_Gain(const QString name,const QString gender,const QString age,const QString id,const QString phone,QWidget* parent=nullptr);
    ~fcpt_Gain();

private slots:
    void on_pushButton_clicked();
    void updateFrame();
    void drawFaceRectangles(cv::Mat &frame);
    //void insert(QString name,QString gender,QString age,QString id, QString phone,QString face_feature);


private:
    Ui::fcpt_Gain *ui;
    QTimer * frameTimer;
    cv::VideoCapture capture;
    cv::Mat frame;
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

#endif // FCPT_GAIN_H
