#include "dbmanager.h"
#include <QStringList>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DbManager::DbManager()
{

}

bool DbManager::init()
{
    return init_db() && createDbStructure();
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

bool DbManager::createDbStructure()
{
    bool r = true;
    qDebug() << "createTable tracks: " << createTable("tracks",
                    {
                        "id integer primary key AUTOINCREMENT",
                        "date_current_day varchar(16)",
                        "time_start varchar(16)",
                        "time_end varchar(16)",
                        "task_target varchar(64)",
                        "task_desc varchar(128)"
                     });
    return r;
}

bool DbManager::createTable(const QString tableName, const QStringList &fieldsData)
{
    QSqlQuery query;
    QString qStr = "CREATE TABLE IF NOT EXISTS %1(%2)";
    qStr = qStr.arg(tableName).arg(fieldsData.join(","));
    qDebug() << "query: " << qStr;
    bool r = query.exec(qStr);
    if(!r) {
        QSqlError err = query.lastError();
        qDebug() << "creating table error: " << err.text();
    }
    return r;
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

