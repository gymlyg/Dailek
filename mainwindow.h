#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include "tracksqlmodel.h"
#include "dbtracks.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool init();
    void displayStatistics();

public slots:
    void on_pushButton_addNew_clicked();
private:
    Ui::MainWindow *ui;
    DbManager m_dbManager;
    TrackSqlModel *m_pTrackSqlModel;
    DbTracks m_dbTracks;
};
#endif // MAINWINDOW_H
