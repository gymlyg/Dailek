#ifndef DBTRACKS_H
#define DBTRACKS_H

#include "dbtable.h"

class DbTracks : public DbTable
{
public:
    static const quint64 ONE_DAY_TOTAL_SECONDS = 24 * 3600;
    DbTracks();
    bool updateLastRecordTM();
    bool updateStatistics(QStringList &statData);
    bool createDayRecord();
};

#endif // DBTRACKS_H
