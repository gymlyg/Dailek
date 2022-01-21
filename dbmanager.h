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
    const QStringList m_slTracksFields = {
        "id integer primary key AUTOINCREMENT",
        "date_current_day integer",
        "time_start integer",
        "time_end integer",
        "task_target varchar(64)",
        "task_desc varchar(128)"
     };
    enum fields {
        FIELD_NAME,
        FIELD_TYPE
    };
    enum prep {
        PREP_FIELD_NAMES,
        PREP_VALUES,
    };
public:
    QSqlDatabase m_db;

    DbManager();
    bool init();
    bool init_db();
    bool createDbStructure();
    bool createTable(const QString tableName, const QStringList &fieldsData);
    bool createRecord(const QString tableName, const QStringList &fieldsData, const QVariantList &values);
    bool createFileByPath( QString dbFilePath);
    bool createDirPath(QString dirPath);
    bool createDayRecord();
    bool updateLastRecordTM();
    bool updateStatistics(QStringList &statData);
    static QStringList prepareValues(const QStringList &fieldsData, const QVariantList& values);
};

#endif // DBMANAGER_H
