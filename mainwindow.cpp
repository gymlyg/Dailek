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
    ui->tableView_day_tracks->show();
    return true;
}

void MainWindow::on_pushButton_addNew_clicked() {
    m_dbManager.createDayRecord();
}
