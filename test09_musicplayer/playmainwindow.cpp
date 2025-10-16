#include "playmainwindow.h"
#include "ui_playmainwindow.h"
#include "logindialog.h"

PlayMainWindow::PlayMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayMainWindow)
{
    ui->setupUi(this);
    //设置窗口图标
    setWindowIcon(QIcon(":/icon/R-C.png"));
    //设置窗口标题
    setWindowTitle("享乐APP");
    //初始化指针
    player = new QMediaPlayer(this);
    playList = new QMediaPlaylist(this);
    videoWidget = new QVideoWidget(ui->verticalLayoutWidget);
    //把视频组件加入到多媒体播放中
    player->setVideoOutput(videoWidget);
    //把当前的视频组件添加到布局
    ui->verticalLayout_video->addWidget(videoWidget);
    //设置布局中心组件的样式表-》背景透明
    ui->verticalLayoutWidget->setStyleSheet("background: transparent;");
    //设置视频组件的可见性
    videoWidget->setVisible(false);
    //当音乐发生改变时（切歌的时候），列表发出信号(自动播放下一首)
    connect(playList,&QMediaPlaylist::currentIndexChanged,
            this,&PlayMainWindow::slot_currentIndexChanged);
    //当进度条发送改变 ，更改进度
    connect(player,&QMediaPlayer::positionChanged,
            this,&PlayMainWindow::slot_positionChanged);
}

PlayMainWindow::~PlayMainWindow()
{
    delete ui;
}

void PlayMainWindow::initLyric()
{
    //获取当前播放歌曲的下标
    int index =  playList->currentIndex();
    //获取文件名
    QString musicName =  musicList[index];
    qDebug()<<musicName;
    //replace:替换
    musicName = musicName.replace(".mp4","");
    //split:分割
    QString singer = musicName.split(" - ")[0];
    QString title = musicName.split(" - ")[1];
    //显示歌手和歌曲名
    ui->label_singer->setText(singer);
    ui->label_title->setText(title);
    //正在播放
    QString str = "正在播放："+ musicName;
    ui->label_current->setText(str);
}

void PlayMainWindow::on_pushButton_change_clicked()
{
    //用消息提示框提问是否要登录
    int choose = QMessageBox::question(this,"登录","确定是登录/切换账号吗？",
                                       QMessageBox::Yes|QMessageBox::No);
    if(choose == QMessageBox::Yes)
    {
        //页面跳转
        LoginDialog *l = new LoginDialog;
        //显示页面
        l->show();
        //关闭页面
        this->close();
    }
}

void PlayMainWindow::on_pushButton_list_clicked()
{
    //打开文件夹对话框-》选择包含音乐文件的文件夹
    QString path = QFileDialog::getExistingDirectory(this,"选择文件","D:/music");
    qDebug()<<path;
    //判断文件夹是否为空
    if(path.isEmpty())
    {
        return;
    }
    //清空列表
    ui->listWidget_musiclist->clear();
    musicList.clear();
    //根据目录过滤你想要音乐文件(mp4)
    QDir dir(path,"*.mp4");
    //获取过滤的文件
    musicList = dir.entryList(QDir::Files,QDir::Name);
    //遍历
    for(auto name : musicList)
    {
        //音乐文件显示在listwidget
        ui->listWidget_musiclist->addItem(name);
        //拼接路径
        QString str = path+"/" +name;
        qDebug()<<str;
        //给播放列表添加媒体
        playList->addMedia(QUrl(str));
    }
    //添加播放列表
    player->setPlaylist(playList);
    //设置播放第一首歌
    playList->setCurrentIndex(0);
    //设置列表播放
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    //设置播放的音量
    player->setVolume(50);
}

void PlayMainWindow::on_pushButton_play_pause_clicked()
{
    qDebug()<<"state:"<<player->state();
    //判断是否为停止播放状态
    if(player->state() == QMediaPlayer::StoppedState ||
            player->state() == QMediaPlayer::PausedState)
    {
        //显示视频
        videoWidget->show();
        player->play();//播放
        //修改图标
        ui->pushButton_play_pause->setIcon(QIcon(":/icon/pause.png"));
        //显示歌曲相关
        initLyric();
    }
    else if(player->state() == QMediaPlayer::PlayingState)
    {
        //暂停
        player->pause();
        //修改图标
        ui->pushButton_play_pause->setIcon(QIcon(":/icon/play.png"));
    }
}

void PlayMainWindow::on_pushButton_next_clicked()
{
    //判断是否有歌
    if(playList->mediaCount()<=0)
    {
        //消息提示框
        QMessageBox::warning(this,"警告","未设置歌单！");
        return;
    }
    //判断是否为停止播放状态
    if(player->state() == QMediaPlayer::StoppedState ||
            player->state() == QMediaPlayer::PausedState)
    {
        //显示视频
        videoWidget->show();
        player->play();//播放
        //修改图标
        ui->pushButton_play_pause->setIcon(QIcon(":/icon/pause.png"));
    }
    //下一曲
    playList->next();
}

void PlayMainWindow::on_pushButton_previous_clicked()
{
    //判断是否有歌
    if(playList->mediaCount()<=0)
    {
        //消息提示框
        QMessageBox::warning(this,"警告","未设置歌单！");
        return;
    }
    //判断是否为停止播放状态
    if(player->state() == QMediaPlayer::StoppedState ||
            player->state() == QMediaPlayer::PausedState)
    {
        //显示视频
        videoWidget->show();
        player->play();//播放
        //修改图标
        ui->pushButton_play_pause->setIcon(QIcon(":/icon/pause.png"));
    }
    //上一曲
    playList->previous();
}

void PlayMainWindow::slot_currentIndexChanged(int index)
{
    qDebug()<<"change:"<<index;
    qDebug()<<musicList[index];
    //更新列表的行
    ui->listWidget_musiclist->setCurrentRow(index);
    //更新歌曲信息
    initLyric();
}

void PlayMainWindow::on_listWidget_musiclist_itemDoubleClicked(QListWidgetItem *item)
{
    //判断是否为停止播放状态
    if(player->state() == QMediaPlayer::StoppedState ||
            player->state() == QMediaPlayer::PausedState)
    {
        //显示视频
        videoWidget->show();
        player->play();//播放
        //修改图标
        ui->pushButton_play_pause->setIcon(QIcon(":/icon/pause.png"));
    }
    //更新列表的序号
    int index = ui->listWidget_musiclist->row(item);
    playList->setCurrentIndex(index);
}

void PlayMainWindow::on_horizontalSlider_progress_sliderMoved(int position)
{
    //改变播放位置
    player->setPosition(position);
}

void PlayMainWindow::on_horizontalSlider_volumn_sliderMoved(int position)
{
    //改变音量
    player->setVolume(position);
}

void PlayMainWindow::slot_positionChanged(qint64 position)
{
    //分 商  100/60
    int cmin = position/1000/60;
    //秒 余数 100%60
    int csec = position/1000%60;
    //获取 正在播放的歌曲的长度 单位毫秒
    int len = player->duration()/1000;
    //qDebug()<<len;//315524/1000=315.524s

    int min = len/60;//5
    int sec = len%60;//40
    //字符串的拼接
    //如果得到的结果不够两位，用0进行补充 00 01 05 06
    //          [01:09
    QString currentTime = QString("[%1:%2/%3:%4]").
            //  分钟 宽度为2  十进制 不够0补充
            arg(cmin,  2,      10,   QChar('0')).
            arg(csec,2,10,QChar('0')).
            arg(min,2,10,QChar('0')).
            arg(sec,2,10,QChar('0'));
    qDebug()<<currentTime<<" "<<min<<" "<<sec;
    ui->label_time->setText(currentTime);
    //设置最大值
    ui->horizontalSlider_progress->setMaximum(player->duration());
    //设置当前值
    ui->horizontalSlider_progress->setValue(position);
}

void PlayMainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        playList->setPlaybackMode(QMediaPlaylist::Loop);//列表
    }
    else if(index == 1)
    {
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//单曲循环
    }
    else if(index == 2)
    {
        playList->setPlaybackMode(QMediaPlaylist::Random);//随机播放
    }
    else if(index == 3)
    {
        playList->setPlaybackMode(QMediaPlaylist::Sequential);//顺序播放
    }
}
