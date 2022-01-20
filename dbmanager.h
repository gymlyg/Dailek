#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DbManager
{
private:
    const QString m_sDbName = "local.db";
public:
    QSqlDatabase m_db;
    DbManager();
    bool init();
    bool init_db();
    bool createDbStructure();
    bool createTable(const QString tableName, const QStringList &fieldsData);
    bool createFileByPath( QString dbFilePath);
    bool createDirPath(QString dirPath);
};

#endif // DBMANAGER_H
