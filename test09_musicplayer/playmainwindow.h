#ifndef PLAYMAINWINDOW_H
#define PLAYMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>//文件对话框
#include <QDir>//目录
#include <QDebug>
#include <QMediaPlayer>//多媒体播放
#include <QMediaPlaylist>//多媒体管理列表
#include <QVideoWidget>//视频组件
#include <QListWidgetItem>//行对象

QT_BEGIN_NAMESPACE
namespace Ui { class PlayMainWindow; }
QT_END_NAMESPACE

class PlayMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PlayMainWindow(QWidget *parent = nullptr);
    ~PlayMainWindow();
    //显示歌曲信息
    void initLyric();

private slots:
    void on_pushButton_change_clicked();

    void on_pushButton_list_clicked();

    void on_pushButton_play_pause_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();

    //当切歌时对应槽函数
    void slot_currentIndexChanged(int index);

    void on_listWidget_musiclist_itemDoubleClicked(QListWidgetItem *item);

    void on_horizontalSlider_progress_sliderMoved(int position);

    void on_horizontalSlider_volumn_sliderMoved(int position);

    //当进度条发送改变时
    void slot_positionChanged(qint64 position);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::PlayMainWindow *ui;
    QStringList musicList;//创建保存歌单的容器
    QMediaPlayer *player;//创建多媒体播放类对象
    QMediaPlaylist *playList;//创建多媒体播放列表类对象
    QVideoWidget *videoWidget;//创建视频组件类对象
};
#endif // PLAYMAINWINDOW_H
