#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QStringList>
#include <QSqlDatabase>

class DbManager
{
private:
    const QString m_sDbName = "local.db";
    const QStringList m_slTracksFields = {
        "id integer primary key AUTOINCREMENT",
        "date_current_day varchar(16)",
        "time_start varchar(16)",
        "time_end varchar(16)",
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
    bool createRecord(const QString tableName, const QStringList &fieldsData, const QStringList &values);
    bool createFileByPath( QString dbFilePath);
    bool createDirPath(QString dirPath);
    bool createDayRecord();
    static QStringList prepareValues(const QStringList &fieldsData, const QStringList& values);
};

#endif // DBMANAGER_H
