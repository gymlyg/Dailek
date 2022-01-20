#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    m_dbManager.init();
    m_pTrackSqlModel = new TrackSqlModel();
    m_pTrackSqlModel->selQuery();
    ui->tableView_day_tracks->setModel(m_pTrackSqlModel);

    m_pTrackSqlModel->setHeaderData(1, Qt::Horizontal, tr("col 1"));
    m_pTrackSqlModel->setHeaderData(2, Qt::Horizontal, tr("col 2"));
    m_pTrackSqlModel->setHeaderData(3, Qt::Horizontal, tr("col 3"));
    m_pTrackSqlModel->setHeaderData(4, Qt::Horizontal, tr("col 4"));

    ui->tableView_day_tracks->hideColumn(0);
    ui->tableView_day_tracks->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_day_tracks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_day_tracks->resizeColumnToContents(true);

    ui->tableView_day_tracks->show();
    return true;
}

void MainWindow::on_pushButton_addNew_clicked() {
    m_dbManager.createDayRecord();
}
