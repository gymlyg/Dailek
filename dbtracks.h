#ifndef DBTRACKS_H
#define DBTRACKS_H

#include "dbtable.h"

class DbTracks : public DbTable
{
public:
    DbTracks();
    bool updateLastRecordTM();
    bool updateStatistics(QStringList &statData);
    bool createDayRecord();
};

#endif // DBTRACKS_H
