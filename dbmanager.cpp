#include "dbmanager.h"
#include <QStringList>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

DbManager::DbManager()
{

}

bool DbManager::init()
{
    return init_db();
}

bool DbManager::init_db()
{
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QString dbPath;

    if(locations.size() > 0) {
        dbPath = QDir::toNativeSeparators(locations[0]);
        dbPath = dbPath
                + QDir::separator() + "db"
                + QDir::separator() + m_sDbName;
        qDebug() << dbPath;
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(dbPath);
        return m_db.open();
    }
    return false;
}
