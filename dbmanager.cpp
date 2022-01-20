#include "dbmanager.h"
#include <QStringList>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QSqlError>
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
    QString dbPath, dirPath;

    if(locations.size() > 0) {

        dirPath = locations[0] + "/db";
        dbPath = dirPath + "/" + m_sDbName;
        qDebug() << "db path: " << dbPath;
        qDebug() << "check db dir path: " << createDirPath(dirPath);
        bool r = createFileByPath(dbPath);
        qDebug() << "check db path: " << r;
        if(r) {
            m_db = QSqlDatabase::addDatabase("QSQLITE");
            m_db.setDatabaseName(dbPath);
            bool dbOpenrez = m_db.open();
            qDebug() << "db opening: " << dbOpenrez;
            if(!dbOpenrez) {
                  QSqlError err = m_db.lastError();
                  qDebug() << "Db error: " << err.text();
            }
            return dbOpenrez;
        }
        qDebug() << "db file cannot be created!";
    }
    return false;
}

bool DbManager::createFileByPath(QString dbFilePath)
{
    QFile dbFile(dbFilePath);
    bool rez = dbFile.open(QIODevice::WriteOnly);
    dbFile.close();
    return rez;
}

bool DbManager::createDirPath(QString dirPath)
{
    QDir dbDir(dirPath);
    if(!dbDir.exists())
        return dbDir.mkpath(".");
    return true;
}

