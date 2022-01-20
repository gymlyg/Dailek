#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>

class DbManager
{
private:
    const QString m_sDbName = "local.db";
public:
    DbManager();
    bool init();
    bool init_db();
};

#endif // DBMANAGER_H
