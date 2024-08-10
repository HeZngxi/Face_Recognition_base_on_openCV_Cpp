#ifndef FACPT_FACEGAIN_H
#define FACPT_FACEGAIN_H

#include <QDialog>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <QTimer>
#include <QMessageBox>
#include <QImage>
#include <fstream>
#include <vector>

namespace Ui {
class facpt_FaceGain;
}

class facpt_FaceGain : public QDialog
{
    Q_OBJECT

public:
    explicit facpt_FaceGain(QWidget *parent = nullptr);
    ~facpt_FaceGain();

private slots:
    void on_pushButton_clicked();
    void updateFrame();
    void drawFaceRectangles(cv::Mat &frame);


private:
    Ui::facpt_FaceGain *ui;
    QTimer * frameTimer;
    cv::VideoCapture capture;
    cv::Mat frame;
    cv::CascadeClassifier faceCascade;
    bool isCameraOpen=false;
};

#endif // FACPT_FACEGAIN_H
