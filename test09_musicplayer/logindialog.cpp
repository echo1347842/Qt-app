#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //播放gif动图
    QMovie *m_Movie = new QMovie(this);
    //设置动图
    m_Movie->setFileName(":/icon/background.gif");
    //缩放大小
    m_Movie->setScaledSize(ui->label->size());
    //在标签上添加
    ui->label->setMovie(m_Movie);
    //开启动图
    m_Movie->start();
    //设置窗口图像
    setWindowIcon(QIcon(":/icon/R-C.png"));
    //设置窗口标题
    setWindowTitle("登录");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_register_clicked()
{
    //页面跳转
    RegisterDialog *r = new RegisterDialog(this);
    //连接
    connect(r,&RegisterDialog::sendId,this,&LoginDialog::recvId);
    //显示窗口
    r->show();
}

void LoginDialog::recvId(int id)
{
    //显示账号
    ui->lineEdit_name->setText(QString::number(id));
}

void LoginDialog::on_pushButton_login_clicked()
{
    //获取文本内容
    QString name = ui->lineEdit_name->text();
    QString pass = ui->lineEdit_password->text();
    //比对数据：根据输入的账号密码
    bool result = UserDao::getUd()->selectTable(name.toInt(),pass);

    if(result)
    {
        //关闭页面
        this->close();
        //判断结果如果登录成功跳转到音乐播放界面
        PlayMainWindow *pw = new PlayMainWindow(this);
        pw->show();
    }
    else
    {
        //消息提示框
        QMessageBox::warning(this,"警告","请再次确认登录账号和密码！");
    }
}
