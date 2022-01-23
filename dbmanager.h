#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QSqlDatabase>

class DbManager
{
private:
    const QString m_sDbName = "local.db";
public:
    QSqlDatabase m_db;

    DbManager();
    //bool init();
    bool init_db();
   // bool createDbStructure();
   // bool createTable(const QString tableName, const QStringList &fieldsData);
    //bool createRecord(const QString tableName, const QStringList &fieldsData, const QVariantList &values);
    bool createFileByPath( QString dbFilePath);
    bool createDirPath(QString dirPath);
    //bool createDayRecord();
   // bool updateLastRecordTM();
    //bool updateStatistics(QStringList &statData);
    //static QStringList prepareValues(const QStringList &fieldsData, const QVariantList& values);
};

#endif // DBMANAGER_H
