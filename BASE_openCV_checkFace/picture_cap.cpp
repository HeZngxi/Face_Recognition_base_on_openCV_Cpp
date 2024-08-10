#include "picture_cap.h"
#include "ui_picture_cap.h"

Picture_Cap::Picture_Cap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Picture_Cap)
{
    ui->setupUi(this);

    detector = dlib::get_frontal_face_detector();
    try {
        dlib::deserialize("D:/Dlib/shape_predictor_68_face_landmarks.dat")>>predictor;
        //predictor = dlib::deserialize<dlib::shape_predictor>("D:\\Dlib\\shape_predictor_68_face_landmarks.dat");
     } catch (dlib::error& e) {
         QMessageBox::warning(this, "错误", "加载模型失败: " + QString::fromStdString(e.what()));
     }
}



Picture_Cap::~Picture_Cap()
{
    delete ui;
}

void Picture_Cap::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("选择图片"),
        "",
        tr("Images (*.png *.jpg *.bmp)"));

    if (!fileName.isEmpty()) {
        pixmap.load(fileName);
        ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio));
    }


     // 转换QPixmap为cv::Mat
    QImage image = pixmap.toImage().scaled(640, 480, Qt::KeepAspectRatio);
    cv::Mat frame = cv::Mat(image.height(), image.width(), CV_8UC3, (uchar*)image.bits(), image.bytesPerLine());
    // 转换cv::Mat为dlib可以处理的格式
    dlib::cv_image<dlib::bgr_pixel> dlibImg(frame);
    // 使用dlib检测人脸
    std::vector<dlib::rectangle> faces = detector(dlibImg);
    // 检测到人脸时提取特征点并绘制`
    for (const auto& face : faces) {
        dlib::full_object_detection shape = predictor(dlibImg, face);

        for (int i = 0; i < shape.num_parts(); i++) {
         const dlib::point& p = shape.part(i);
         qDebug() << "Landmark " << i << ": (" << p.x() << ", " << p.y() << ")";
        }
    }
    ui->pushButton->setText("人脸检测完成");
}
