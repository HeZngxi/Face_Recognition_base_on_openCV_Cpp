#ifndef DELETE_INFO_H
#define DELETE_INFO_H

#include <QDialog>
#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <filedelet.h>

namespace Ui {
class Delete_info;
}

class Delete_info : public QDialog
{
    Q_OBJECT

public:
    explicit Delete_info(QWidget *parent = nullptr);
    ~Delete_info();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Delete_info *ui;
    QString id;
};

#endif // DELETE_INFO_H
