#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "tracksdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::init()
{
    m_dbManager.init_db();
    m_dbTracks.init();
    m_pTrackSqlModel = new TrackSqlModel();
    m_pTrackSqlModel->selQuery();

    ui->tableView_day_tracks->setItemDelegate(new TracksDelegate());
    ui->tableView_day_tracks->setModel(m_pTrackSqlModel);

    m_pTrackSqlModel->setHeaderData(1, Qt::Horizontal, tr("From"));
    m_pTrackSqlModel->setHeaderData(2, Qt::Horizontal, tr("To"));
    m_pTrackSqlModel->setHeaderData(3, Qt::Horizontal, tr("Period"));
    m_pTrackSqlModel->setHeaderData(4, Qt::Horizontal, tr("TrackType"));
    m_pTrackSqlModel->setHeaderData(5, Qt::Horizontal, tr("TrackDesc"));

    ui->tableView_day_tracks->hideColumn(0);
    ui->tableView_day_tracks->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_day_tracks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_day_tracks->resizeColumnToContents(true);

    ui->tableView_day_tracks->show();
    displayStatistics();
    return true;
}

void MainWindow::displayStatistics()
{
    QStringList statData;
    QString statMsg;
    m_dbTracks.updateStatistics(statData);
    if(statData.size() > 0) {
        qDebug() << "statData: " << statData;
        statMsg = tr("Per day: %1").arg(statData.join("; "));
        statusBar()->showMessage(statMsg);
    }
}

void MainWindow::on_pushButton_addNew_clicked()
{
    m_dbTracks.updateLastRecordTM();
    m_dbTracks.createDayRecord();
    m_pTrackSqlModel->setTodaySelQuery();
    m_pTrackSqlModel->selQuery();
    displayStatistics();
}
