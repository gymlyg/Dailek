#include "dbmanager.h"
#include <QStringList>
#include <QStandardPaths>

DbManager::DbManager()
{

}

bool DbManager::init()
{
    return true;
}

bool DbManager::init_db()
{
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QStringList appDataSubDirs;
    appDataSubDirs.append("db");
    QString db_path = locations[0] + "/db/" + m_sDbName;
}
