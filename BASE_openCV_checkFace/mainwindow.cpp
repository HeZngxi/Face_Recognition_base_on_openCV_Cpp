#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("人脸检测程序");
    this->setStyleSheet("QMainWindow {background-image:url(D:/CODE_File/2024SummerS/QT/FacePicture/780.jpg)}");
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()      //登陆界面三个选择的按钮1
{
    FaceCpt* facecpt=new FaceCpt(this);
    //this->setEnabled(false);
    facecpt->setWindowTitle("人脸信息录入");
    facecpt->setStyleSheet("QDialog {background-image:url(D:/CODE_File/2024SummerS/QT/FacePicture/3320717_164433075130_2)}");
    facecpt->setFixedSize(800,563);
    facecpt->show();
    facecpt->exec();
    //this->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()     //登陆界面三个选择的按钮2
{
    InfoChge* infochge=new InfoChge(this);
    //this->setEnabled(false);
    infochge->setWindowTitle("更改人员信息");
    infochge->setStyleSheet("QDialog {background-image:url(D:/CODE_File/2024SummerS/QT/Facepicture/3320717_164433075130_2)}");
    infochge->setFixedSize(800,563);
    infochge->show();
    infochge->exec();
    //this->setEnabled(true);
}

void MainWindow::on_pushButton_3_clicked()      //登陆界面三个选择的按钮3
{
    FaceCk* faceck=new FaceCk(this);
    //this->setEnabled(false);
    faceck->setWindowTitle("人脸检测");
    faceck->setStyleSheet("QDialog {background-image:url(D:/CODE_File/2024SummerS/QT/FacePicture/3320717_164433075130_2)}");
    faceck->setFixedSize(800,563);
    faceck->show();
    faceck->exec();
    //this->setEnabled(true);
}
