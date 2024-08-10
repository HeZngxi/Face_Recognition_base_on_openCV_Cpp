#include "delete_info.h"
#include "ui_delete_info.h"
#include <QDebug>
Delete_info::Delete_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete_info)
{
    ui->setupUi(this);
    setFixedSize(400,300);
}

Delete_info::~Delete_info()
{
    delete ui;
}

void Delete_info::on_pushButton_clicked()

{
    QString id=ui->iDALineEdit->text();
    qDebug()<<id;
    FileDelet * fidl=new FileDelet(id);
}
