#include "infochge.h"
#include "ui_infochge.h"

InfoChge::InfoChge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoChge)
{
    ui->setupUi(this);
}

InfoChge::~InfoChge()
{
    delete ui;
}

void InfoChge::on_pushButton_clicked()
{
    QString name =ui->aLineEdit->text();
    QString gender = ui->zComboBox->currentText();
    QString age=ui->cLineEdit->text();
    QString id=ui->iDLLineEdit->text();
    QString phone=ui->mLineEdit->text();
    Face_match* match =new Face_match(name,gender,age,id,phone);
    match->setWindowTitle("人脸采集");
    match->setStyleSheet("QDialog {background-image:url(D:/CODE_File/2024SummerS/QT/FacePicture/3320717_164433075130_2)}");
    match->show();
    match->exec();
}

void InfoChge::on_pushButton_2_clicked()
{
    Delete_info * dl=new Delete_info;
    dl->setWindowTitle("信息删除窗口");
    dl->setStyleSheet("QDialog {background-image:url(D:/CODE_File/2024SummerS/QT/FacePicture/3320717_164433075130_2)}");
    dl->show();
    dl->exec();
}
