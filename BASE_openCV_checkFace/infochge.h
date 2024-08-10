#ifndef INFOCHGE_H
#define INFOCHGE_H

#include <QDialog>
#include <face_match.h>
#include <delete_info.h>

namespace Ui {
class InfoChge;
}

class InfoChge : public QDialog
{
    Q_OBJECT

public:
    explicit InfoChge(QWidget *parent = nullptr);
    ~InfoChge();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::InfoChge *ui;
};

#endif // INFOCHGE_H
