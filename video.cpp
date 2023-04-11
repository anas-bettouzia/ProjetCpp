#include "video.h"
#include "ui_video.h"
#include <QFileDialog>
#include<QDialog>
#include <QToolButton>
#include <QDir>

video::video(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video)
{
    ui->setupUi(this);
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track")
                                                            << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    m_player = new QMediaPlayer(this);          // Init player
    m_playlist = new QMediaPlaylist(m_player);  // Init playlist
    m_player->setPlaylist(m_playlist);
    m_player->setVolume(70);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);  // Set circular play mode playlist

    // подключаем кнопки управления к слотам управления
    // Here we note that the navigation is done through the playlist playlist
    // and start / pause / stop via the player itself
    connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);

    // When you doubleclick on the track in the table set the track in the playlist
    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        m_playlist->setCurrentIndex(index.row());
    });

    // if the current track of the index change in the playlist, set the file name in a special label
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
    });
}

video ::~video ()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
}

void video ::on_btn_add_clicked()
{
    // Using the file selection dialog to make multiple selections of mp3 files
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.mp3)"));

    // Next, set the data names and file paths
    // into the playlist and table displaying the playlist
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
}
