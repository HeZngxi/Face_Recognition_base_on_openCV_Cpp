#include "facpt_facegain.h"
#include "ui_facpt_facegain.h"

facpt_FaceGain::facpt_FaceGain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facpt_FaceGain)
{
    ui->setupUi(this);
    ui->setupUi(this);
    resize(800,600);
    ui->label->resize(640,480);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640); // 设置帧宽度（根据label大小调整）
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480); // 设置帧高度（根据label大小调整）

    faceCascade.load("D:/OpenCV/opencv-4.5.4/buildQt/install/etc/haarcascades/haarcascade_frontalface_default.xml");
    if (faceCascade.empty()) {
       QMessageBox::warning(this, "错误", "加载人脸检测模型失败！");
    }
}

facpt_FaceGain::~facpt_FaceGain()
{
    if (capture.isOpened()) {
        capture.release();
    }
    if (frameTimer) {
        frameTimer->stop();
        delete frameTimer;
    }
    delete ui;
}

void facpt_FaceGain::on_pushButton_clicked()
{
    if(isCameraOpen==false){
       capture.open(0);
       if(!ui->label->isVisible()){
          ui->label->show();
       }
       if (!capture.isOpened()) {
          QMessageBox::warning(this, "错误", "无法打开摄像头！");
          return;
       }

     frameTimer = new QTimer(this);
     connect(frameTimer, &QTimer::timeout, this, &facpt_FaceGain::updateFrame);
     frameTimer->start(30); // 约30帧每秒
     ui->pushButton->setText("点击关闭摄像头");
     isCameraOpen=true;


    }else{
       frameTimer->stop();
       ui->pushButton->setText("点击打开摄像头");
       ui->label->hide();
       isCameraOpen=false;
    }

}

void facpt_FaceGain::updateFrame() {
    cv::Mat frame;
    if (capture.read(frame)) {
        QImage image;
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        std::vector<cv::Rect> faces;

        faceCascade.detectMultiScale(grayFrame, faces, 1.1, 3, 0, cv::Size(30, 30));

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0));
        }

        image = QImage((uchar*)frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888).rgbSwapped();
        QPixmap pixmap = QPixmap::fromImage(image);
        ui->label->setPixmap(pixmap);
    } else {
        QMessageBox::warning(this, "错误", "无法从摄像头读取帧！");
        frameTimer->stop();
        capture.release();
    }
}
void facpt_FaceGain::drawFaceRectangles(cv::Mat &grayFrame) {
    std::vector<cv::Rect> faces;

    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 3, 0, cv::Size(30, 30));
    for (const auto& face : faces) {
        cv::rectangle(grayFrame, face, cv::Scalar(0, 255, 0));
    }
}

