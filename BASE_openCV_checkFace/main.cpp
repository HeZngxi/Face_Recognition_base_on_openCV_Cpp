#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(780,488);
    w.show();

    //建立数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sqlite_Qt/Qt_FaceInfor.db");
    if (!db.open()) {
        qDebug() << "无法打开数据库: " << db.lastError().text();
        return 1;
    }
    // 检查表是否存在，如果不存在则创建
    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='faces'");
    if (!query.exec()) {
        qDebug() << "查询失败: " << query.lastError();
        return 1;
    }

    bool tableExists = false;
    while (query.next()) {
        if (query.value(0).toString() == "faces") {
            tableExists = true;
            break;
        }
    }

    if (!tableExists) {
        if (!QSqlQuery().exec("CREATE TABLE faces ("
                              "id TEXT PRIMARY KEY,"
                              "name TEXT NOT NULL,"
                              "gender TEXT NOT NULL,"
                              "age TEXT NOT NULL,"
                              "phone TEXT NOT NULL,"
                              "face_features TEXT NOT NULL)")) {
            qDebug() << "创建表失败: " << QSqlQuery().lastError();
        }
    }

    return a.exec();
}
