#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QMessageBox>//消息提示框
#include "userdao.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_pushButton_clicked();

signals://自定义信号发送注册成功的账号
    void sendId(int id);

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
