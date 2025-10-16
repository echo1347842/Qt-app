#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMovie>
#include "registerdialog.h"
#include "playmainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_pushButton_register_clicked();
    //接收注册页面的自定义信号
    void recvId(int id);

    void on_pushButton_login_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
