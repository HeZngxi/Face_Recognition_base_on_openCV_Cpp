#ifndef FACECPT_H
#define FACECPT_H

#include <QDialog>
#include <fcpt_gain.h>
#include <picture_cap.h>

namespace Ui {
class FaceCpt;
}

class FaceCpt : public QDialog
{
    Q_OBJECT

public:
    explicit FaceCpt(QWidget *parent = nullptr);
    ~FaceCpt();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FaceCpt *ui;
};

#endif // FACECPT_H
