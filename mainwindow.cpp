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

    m_pTrackSqlModel->setHeaderData(1, Qt::Horizontal, tr("От"));
    m_pTrackSqlModel->setHeaderData(2, Qt::Horizontal, tr("До"));
    m_pTrackSqlModel->setHeaderData(3, Qt::Horizontal, tr("Период"));
    m_pTrackSqlModel->setHeaderData(4, Qt::Horizontal, tr("Тип"));
    m_pTrackSqlModel->setHeaderData(5, Qt::Horizontal, tr("Описание"));

    ui->tableView_day_tracks->hideColumn(0);
    ui->tableView_day_tracks->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_day_tracks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_day_tracks->resizeColumnToContents(true);

    ui->tableView_day_tracks->show();
    return true;
}

void MainWindow::on_pushButton_addNew_clicked()
{
    QStringList statData;
    QString statMsg;
    m_dbTracks.updateLastRecordTM();
    m_dbTracks.createDayRecord();
    m_pTrackSqlModel->selQuery();
    m_dbTracks.updateStatistics(statData);
    if(statData.size() > 0) {
        qDebug() << "statData: " << statData;
        statMsg = "Среднее за день: %1";
        statMsg = statMsg.arg(statData[0]);
        statusBar()->showMessage(statMsg);
    }

}
