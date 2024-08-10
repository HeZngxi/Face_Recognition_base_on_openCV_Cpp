#include "face_match.h"
#include "ui_face_match.h"

Face_match::Face_match(const QString name,const QString gender,const QString age,const QString id,const QString phone,QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Face_match),
    mname(name),
    mgender(gender),
    mage(age),
    mid(id),
    mphone(phone)
{

    ui->setupUi(this);
    resize(800,600);
    ui->label->resize(640,480);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    detector = dlib::get_frontal_face_detector();
    try {
        dlib::deserialize("D:/Dlib/shape_predictor_68_face_landmarks.dat")>>predictor;
        //predictor = dlib::deserialize<dlib::shape_predictor>("D:\\Dlib\\shape_predictor_68_face_landmarks.dat");
     } catch (dlib::error& e) {
         QMessageBox::warning(this, "错误", "加载模型失败: " + QString::fromStdString(e.what()));
     }

    faceCascade.load("D:/OpenCV/opencv-4.5.4/buildQt/install/etc/haarcascades/haarcascade_frontalface_default.xml");
    if (faceCascade.empty()) {
        QMessageBox::warning(this, "错误", "加载人脸检测模型失败！");
    }
}

Face_match::~Face_match()
{
    if (capture.isOpened()) {
        capture.release();
    }
    delete ui;
    if (frameTimer) {
        frameTimer->stop();
        delete frameTimer;
    }
}

void Face_match::on_pushButton_clicked()
{
    if(isCameraOpen==false){
       capture.open(0);
       if(!ui->label->isVisible()){
          ui->label->show();
       }
       if(!capture.isOpened()) {
         QMessageBox::warning(this, "错误", "无法打开摄像头！");
         return;
       }

       frameTimer = new QTimer(this);
       connect(frameTimer, &QTimer::timeout, this, &Face_match::updateFrame);
       frameTimer->start(30); // 约30帧每秒
       ui->pushButton->setText("点击关闭摄像头");
       isCameraOpen=true;
       }else{
        frameTimer->stop();
        ui->pushButton->setText("点击打开摄像头");
        ui->label->hide();
        isCameraOpen=false;
        hasCapturedFace = false; // 重置标志变量
        capture.release();
       }
}

void Face_match::updateFrame() {
    cv::Mat frame;
    if (capture.read(frame)) {
        std::vector<cv::Mat> channels(3);
        split(frame,channels);
        for(int j = 0; j < 3; j++){
          equalizeHist(channels[j],channels[j]);
        }//光线补偿
        merge(channels,frame);
    dlib::cv_image<dlib::bgr_pixel> dlibImg(frame);
    std::vector<dlib::rectangle> faces = detector(dlibImg);
    if (!faces.empty() && !hasCapturedFace){
        for (const auto& face : faces) {
            dlib::full_object_detection shape = predictor(dlibImg, face);

            QStringList faceFeatureList; // 创建一个用于存储特征点坐标的列表

            for (int i = 0; i < shape.num_parts(); i++) {
                const dlib::point& p = shape.part(i);
                // 将特征点坐标转换为字符串，并添加到列表中
                faceFeatureList.append(QString::number(p.x()) + "," + QString::number(p.y()));
            }

            // 使用特定的分隔符（例如逗号）将所有特征点坐标连接成一个字符串
            QString face_feature = faceFeatureList.join(",");


            for (int i = 0; i < shape.num_parts(); i++) {
                const dlib::point& p = shape.part(i);
                cv::circle(frame, cv::Point(p.x(), p.y()), 2, cv::Scalar(255, 0, 0), -1);
            }



            QString infoLine = mid + "," + mname + "," + mgender + "," + mage + "," + mphone;
            QString filePath = "Basic_info/"+mid+".txt";
            QFile file(filePath);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
               {
                qWarning() << "Failed to open file" << filePath;
                return;
             }

            // 创建一个QTextStream用于写入文件
            QTextStream out(&file);
            // 写入数据
            out << infoLine<< Qt::endl;
            // 关闭文件
            file.close();


            QString faceInfoFilePath = "Face_id/" + mid + ".txt";
            QFile faceInfoFile(faceInfoFilePath);
            if (!faceInfoFile.open(QIODevice::WriteOnly | QIODevice::Text)){
               qWarning() << "Failed to open file" << faceInfoFilePath;
               return;
             }
            QTextStream outFaceInfo(&faceInfoFile);
            outFaceInfo << face_feature << Qt::endl;
            faceInfoFile.close();


        }
        hasCapturedFace=true;
        ui->pushButton->setText("采集完成点击关闭");
    }

    // 转换图像格式以显示
    QImage image = QImage((uchar*)frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888).rgbSwapped();
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label->setPixmap(pixmap);
    } else {
       QMessageBox::warning(this, "错误", "无法从摄像头读取帧！");
       frameTimer->stop();
       capture.release();
    }
}
void Face_match::drawFaceRectangles(cv::Mat &grayFrame) {
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 3, 0, cv::Size(30, 30));
    for (const auto& face : faces) {
        cv::rectangle(grayFrame, face, cv::Scalar(0, 255, 0));
    }
}




