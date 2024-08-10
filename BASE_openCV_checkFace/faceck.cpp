#include "faceck.h"
#include "ui_faceck.h"

FaceCk::FaceCk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceCk)
{
    ui->setupUi(this);
    resize(800,600);
    ui->label->resize(640,380);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 380);

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

FaceCk::~FaceCk()
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

void FaceCk::on_pushButton_clicked()
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
       connect(frameTimer, &QTimer::timeout, this, &FaceCk::updateFrame);
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


void FaceCk::drawFaceRectangles(cv::Mat &grayFrame) {
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 3, 0, cv::Size(30, 30));
    for (const auto& face : faces) {
        cv::rectangle(grayFrame, face, cv::Scalar(0, 255, 0));

    }
}



void FaceCk::updateFrame() {
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
    //这里加载初始化了一个笑脸检测模型
    cv::CascadeClassifier smileCascade;
    smileCascade.load("D:/OpenCV/opencv-4.5.4/data/haarcascades/haarcascade_smile.xml");

    if (!faces.empty() && !hasCapturedFace){
        for (const auto& face : faces) {


            cv::Rect faceRect(face.left(), face.top(), face.width(), face.height());
            cv::Mat faceROI = frame(faceRect); // 提取人脸区域的图像

            // 对人脸区域进行笑脸检测
            std::vector<cv::Rect> smiles;
            smileCascade.detectMultiScale(faceROI, smiles, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));


            // 绘制人脸矩形框
            cv::rectangle(frame, faceRect.tl(), faceRect.br(), cv::Scalar(255, 0, 0), 2);

            // 如果检测到笑脸，弹出信息提示
            if (!smiles.empty()) {
                //QMessageBox::information(nullptr, "检测结果", "检测到笑脸");
                ui->label_2->setText("笑脸检测结果：检测到笑脸");
            }else{
                ui->label_2->setText("笑脸检测结果：未检测到笑脸");
            }


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

            //qDebug()<<face_feature;

            //在这里实现与库中的人脸信息进行匹配，在face的遍历中每一个face信息再与文件中的face信息遍历匹配
            QString folderPath="Face_id/";
            QDir faceDir(folderPath);
            if(!faceDir.exists()){
                QMessageBox::warning(this,"错误","人脸信息库文件不存在");
                return ;
            }
            QStringList filters;
            filters<<"*.txt";
            bool resulte=false;
            QStringList txtfiles=faceDir.entryList(filters,QDir::Files);
            for (const QString &fileName : txtfiles) {
            // 在这里实现将face信息与库文件中的人脸信息进行匹配，并做出提示
                QString filePath = faceDir.absoluteFilePath(fileName); // 获取绝对路径
                QFile file(filePath);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                   qDebug() << "Cannot open file:" << filePath;
                   continue; // 如果文件无法打开，跳过当前文件，继续下一个循环
                }
                QTextStream in(&file);
                QString content=in.readAll().trimmed();
                file.close();
                qDebug()<<content;
                QStringList facefile=content.split(',',QString::SkipEmptyParts);
                QStringList facecapt=face_feature.split(',',QString::SkipEmptyParts);
                resulte=matchFaces(facefile, facecapt);
                if(resulte==true){
                    break;
                }

            }if(resulte==false){
                QMessageBox::information(this,"检测结果","匹配失败");
            }

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



bool FaceCk::matchFaces(const QStringList &facefile, const QStringList &facecapt){
    QVector<int> filearr1;
    QVector<int> filearr2;
    QVector<int> captarr1;
    QVector<int> captarr2;
    bool result=false;
    for(int i=0;i<facefile.size();++i){
        int num=facefile[i].toInt();
        if(i%2==0){
            filearr1.append(num);
        }else{
            filearr2.append(num);
        }
    }
    for (int i=0;i<facecapt.size();++i) {
        int num=facecapt[i].toInt();
        if(i%2==0){
            captarr1.append(num);
        }else{
            captarr2.append(num);
        }

    }
    double distance=0.0;
    for (int i=0;i<filearr1.size();++i) {
       if(filearr1.size()!=captarr1.size()){
           return result;
       }
       double dx=filearr1[i]-captarr1[i];
       double dy=filearr2[i]-captarr2[i];
       distance+=dx*dx+dy*dy;
    }
    distance=std::sqrt(distance);
    qDebug()<<distance;
    double matchDegree;
    if(distance<1000){
        matchDegree=1/(1+distance);
        matchDegree*=7000;
        QString cout="欧氏距离:"+QString::number(distance,'f',1)+'\n'+
                "匹配成功";

                //"匹配度："+QString::number(matchDegree,'f',1)+"%";
        QMessageBox::information(this,"匹配结果",cout);
        distance=0;
        return true;
    }else{
        distance=0;
        return false;
    }

}






