#include "filedelet.h"

FileDelet::FileDelet(QString id)
{

        if (QFile::exists("Basic_info/"+id+".txt")) {
        // 尝试删除文件
        if (QFile::remove("Basic_info/"+id+".txt")) {
            QMessageBox::information(nullptr, "信息", "文件删除成功");
        } else {
            QMessageBox::warning(nullptr, "错误", "文件删除失败");
        }
        } else {
            QMessageBox::warning(nullptr, "错误", "文件不存在");
        }
        QFile::remove("Face_id/"+id+".txt");
}
