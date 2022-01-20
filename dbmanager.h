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
};

#endif // DBMANAGER_H
