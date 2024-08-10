#include "facecpt.h"
#include "ui_facecpt.h"

FaceCpt::FaceCpt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceCpt)
{
    ui->setupUi(this);
}

FaceCpt::~FaceCpt()
{
    delete ui;
}

void FaceCpt::on_pushButton_clicked()               //点击按钮进入摄像头人脸采集窗口
{
    QString name =ui->aLineEdit->text();
    QString gender = ui->zComboBox->currentText();
    QString age=ui->cLineEdit->text();
    QString id=ui->iDLLineEdit->text();
    QString phone=ui->mLineEdit->text();
    //emit fcpt_Gain(name,gender,age,id,phone);

    fcpt_Gain* gain=new fcpt_Gain(name,gender,age,id,phone);
    gain->setWindowTitle("摄像头人脸录入窗口");
    //gain->setFixedSize(800,563);
    gain->setStyleSheet("QDialog {background-image:url(D:/CODE_File/2024SummerS/QT/FacePicture/3320717_164433075130_2)}");
    gain->show();
    gain->exec();

}

void FaceCpt::on_pushButton_2_clicked()              //点击按钮进入图片导入人脸采集窗口
{
    Picture_Cap * pcap=new Picture_Cap;
    pcap->setWindowTitle("图片导入采集窗口");
    pcap->setStyleSheet("QDialog {background-image:url(D:/CODE_File/2024SummerS/QT/FacePicture/3320717_164433075130_2)}");
    pcap->show();
    pcap->exec();

}
