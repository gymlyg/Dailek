#include "dbmanager.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#include <QDate>
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
    qDebug() << "createTable tracks: " << createTable("tracks", m_slTracksFields);
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

bool DbManager::createRecord(const QString tableName, const QStringList &fieldsData, const QVariantList &values)
{
    QSqlQuery query;
    QString qStr = "INSERT INTO %1 (%2) VALUES (%3)";

    QStringList qData = prepareValues(fieldsData, values);

    qStr = qStr.arg(tableName)
            .arg(qData[PREP_FIELD_NAMES])
            .arg(qData[PREP_VALUES]);
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
    bool rez = true;
    QFile dbFile(dbFilePath);
    if(!dbFile.exists()) {
        rez = dbFile.open(QIODevice::WriteOnly);
        dbFile.close();
    }
    return rez;
}

bool DbManager::createDirPath(QString dirPath)
{
    QDir dbDir(dirPath);
    if(!dbDir.exists())
        return dbDir.mkpath(".");
    return true;
}

bool DbManager::createDayRecord()
{
    qint64 dtInt = QDate::currentDate().startOfDay().toSecsSinceEpoch();
    qint64 dtmInt = QDateTime::currentDateTime().toSecsSinceEpoch();
    QVariantList newRec = {QVariant("NULL"),
                           QVariant(dtInt),
                           QVariant(dtmInt),
                           QVariant(0),
                           QVariant(""),
                           QVariant("")};
    return createRecord("tracks", m_slTracksFields, newRec);
}

bool DbManager::updateLastRecordTM()
{
    QSqlQuery q;
    qint64 dtmInt = QDateTime::currentDateTime().toSecsSinceEpoch();
    QString qStr = "UPDATE %1 set time_end = %2 WHERE id = (SELECT id FROM %1 ORDER BY id DESC LIMIT 1)";
    qDebug() << "last tm update query: " << qStr;
    qStr = qStr.arg("tracks").arg(dtmInt);
    return q.exec(qStr);
}

bool DbManager::updateStatistics(QStringList &statData)
{
    bool rez = false;
    QSqlQuery query;
    QDate dt = QDate::currentDate();
    QString qStr = "select sum(time_end - time_start) from tracks where date_current_day = %1";
    qStr = qStr.arg(dt.startOfDay().toSecsSinceEpoch());
    qDebug() << qStr;
    rez = query.exec(qStr);
    if(rez) {
        QSqlRecord record = query.record();
        query.next();
        qDebug() << record << ", amount: " << record.count();
        for(int i = 0; i < record.count(); i++) {
            statData.append(query.value(i).toString());
            qDebug() << "append " << query.value(i).toString();
        }
    } else {
        QSqlError err = query.lastError();
        qDebug() << "update statistics error: " << err.text();
    }
    return rez;
}

QStringList DbManager::prepareValues(const QStringList &fieldsData, const QVariantList& values)
{
    QString valuesStr;
    QStringList fieldsStrLst, valuesStrLst, curFieldList;
    for(int i = 0; i < fieldsData.size(); i++) {
        curFieldList = fieldsData.at(i).split(" ");
        valuesStr = values.at(i).toString();
        if(curFieldList[FIELD_TYPE].contains("text")
                || curFieldList[FIELD_TYPE].contains("varchar")) {
            valuesStr = "'" + valuesStr + "'";
        }
        fieldsStrLst.append(curFieldList[FIELD_NAME]);
        valuesStrLst.append(valuesStr);
    }
    return QStringList({fieldsStrLst.join(", "), valuesStrLst.join(", ")});
}
