#ifndef PICTURE_CAP_H
#define PICTURE_CAP_H

#include <QDialog>
#include <QFileDialog>
#include <iostream>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <QMessageBox>
#include <QImage>
#include <fstream>
#include <vector>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>



namespace Ui {
class Picture_Cap;
}

class Picture_Cap : public QDialog
{
    Q_OBJECT

public:
    explicit Picture_Cap(QWidget *parent = nullptr);
    ~Picture_Cap();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Picture_Cap *ui;
    QPixmap pixmap;
    dlib::frontal_face_detector detector;
    dlib::shape_predictor predictor;
};

#endif // PICTURE_CAP_H
