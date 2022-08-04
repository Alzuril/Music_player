#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMediaPlayer>
//#include <QMediaPlaylist>
#include "playlistmodel.h"
#include "qmediaplaylist.h"
#include <QFileDialog>
#include <QDebug>
#include <QAudioDevice>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();
    void playlistPositionChanged(int currentItem);
    void addToPlaylist(QUrl url);
    void jump(const QModelIndex &index);
    void playClicked();
    void seek(int mseconds);

    void on_play_clicked();

    void on_pause_clicked();

    void on_next_clicked();

private:
    Ui::MainWindow *ui;
    PlaylistModel* playlist_model;
    QMediaPlayer* player;
    //PlaylistModel *playlistModel;
    QMediaPlaylist *playlist;
    QAudioOutput *audioOutput;
};
#endif // MAINWINDOW_H
