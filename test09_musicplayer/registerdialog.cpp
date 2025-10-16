#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //设置窗口标题
    setWindowTitle("注册");
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_pushButton_clicked()
{
    //获取文本内容
    QString name = ui->lineEdit_name->text();
    QString pass = ui->lineEdit_password->text();
    QString repass = ui->lineEdit_repass->text();
    //判断输入的密码是否一致
    if(pass == repass && !pass.isEmpty())
    {
        //调用数据库,保存数据
        int id = UserDao::getUd()->insertTable(name,pass);


        //拼接
        QString str = QString("恭喜你注册成功，注册的账号为 %1").arg(id);
        //消息提示框提示
        QMessageBox::information(this,"注册",str);
        //发送自定义信号
        emit sendId(id);
        //关闭页面
        this->close();
    }
    else
    {
        //消息提示框提示
        QMessageBox::warning(this,"警告","注册失败，请重新注册！");
    }
}
