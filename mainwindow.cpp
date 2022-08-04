#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    playlist_model = new PlaylistModel(this);
    ui->playlist_view->setModel(playlist_model);
    ui->playlist_view->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->playlist_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    playlist = playlist_model->playlist();
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::playlistPositionChanged);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->prev, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);
    connect(ui->next, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->play, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(ui->pause, &QPushButton::clicked, player, &QMediaPlayer::pause);

    connect(ui->playlist_view, &QListView::doubleClicked, [this] (const QModelIndex &index)
        {playlist->setCurrentIndex(index.row());});
    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this] (int index)
        {ui->current_track->setText(playlist_model->data(playlist_model->index(index, 0)).toString());});

    ui->horizontalSlider->setRange(0, player->duration());
    connect(ui->horizontalSlider, &QSlider::sliderMoved, this, &MainWindow::seek);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_clicked()
{
    /*QStringList files = QFileDialog::getOpenFileNames(this, "Open a file", QString(), "Audio Files (*.mp3)");
    //player->setSource(QUrl::fromLocalFile(file_name));
    foreach (QString file_path, files)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(file_path).dirName()));
        items.append(new QStandardItem(file_path));
        playlist_model->appendRow;
    }*/
    /*QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open File"));
    //fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    addToPlaylist(fileDialog.getOpenFileName());*/
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "", "Audio Files(*.mp3)");
    playlist->addMedia(file_name);
    //qDebug()<< player->mediaStatus();
}

void MainWindow::addToPlaylist(QUrl url)
{
    playlist->addMedia(url);
}

void MainWindow::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        playlist->setCurrentIndex(index.row());
    }
}

void MainWindow::playlistPositionChanged(int currentItem)
{
    if (ui->playlist_view)
        ui->playlist_view->setCurrentIndex(playlist_model->index(currentItem, 0));
    player->setSource(playlist->currentMedia());
}

void MainWindow::playClicked()
{
    if (player->playbackState() == QMediaPlayer::PlaybackState::PausedState)
        player->play();
    else if (player->playbackState() == QMediaPlayer::PlaybackState::StoppedState)
        player->play();
    else if (player->playbackState() == QMediaPlayer::PlaybackState::PlayingState)
        player->pause();
}

void MainWindow::seek(int mseconds)
{
    player->setPosition(mseconds);
}

void MainWindow::on_play_clicked()
{
    if (player->mediaStatus() == QMediaPlayer::MediaStatus::LoadedMedia ||
            player->mediaStatus() == QMediaPlayer::MediaStatus::BufferedMedia)
    {
        ui->pause->setEnabled(true);
        ui->play->setEnabled(false);
    }
}


void MainWindow::on_pause_clicked()
{
    if (player->mediaStatus() == QMediaPlayer::MediaStatus::BufferedMedia)
    {
        ui->play->setEnabled(true);
        ui->pause->setEnabled(false);
    }
}


void MainWindow::on_next_clicked()
{
    //player->setAudioOutput(audioOutput);
    //player->play();
    //ui->play->setEnabled(true);
    /*qDebug()<< player->mediaStatus();
    qDebug()<< player->playbackState();
    ui->play->clicked();
    qDebug()<< player->mediaStatus();
    qDebug()<< player->playbackState();*/
}

