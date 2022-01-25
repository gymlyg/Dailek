#include "dbtracks.h"
#include <QDateTime>
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

DbTracks::DbTracks():DbTable(
    "tracks",
    {
        "id integer primary key AUTOINCREMENT",
        "date_current_day integer",
        "time_start integer",
        "time_end integer",
        "task_target varchar(64)",
        "task_desc varchar(128)"
     })
{
}

bool DbTracks::updateLastRecordTM()
{
    QSqlQuery q;
    qint64 dtmInt = QDateTime::currentDateTime().toSecsSinceEpoch();
    QString qStr = "UPDATE %1 set time_end = %2 WHERE id = (SELECT id FROM %1 ORDER BY id DESC LIMIT 1)";
    qDebug() << "last tm update query: " << qStr;
    qStr = qStr.arg(m_sTableName).arg(dtmInt);
    return q.exec(qStr);
}

bool DbTracks::updateStatistics(QStringList &statData)
{
    bool rez = false;
    QSqlQuery query;
    QDate dt = QDate::currentDate();
    QString qStr = "select sum(time_end - time_start) from %1 where date_current_day = %2 and (time_end <> 0 or time_end <> NULL)";
    qStr = qStr.arg(m_sTableName).arg(dt.startOfDay().toSecsSinceEpoch());
    qDebug() << qStr;
    rez = query.exec(qStr);
    if(rez) {
        QSqlRecord record = query.record();
        query.next();
        qDebug() << record << ", amount: " << record.count();
        for(int i = 0; i < record.count(); i++) {
            int c = query.value(i).toInt();
            int h = c / 3600;
            int m = c % 3600 / 60;
            QString dateString = QString("%1:%2").arg(h, 4, 'g', -1, '0').arg(m, 2, 'g', -1, '0');
            statData.append(dateString);
            qDebug() << "append " << query.value(i).toString();
        }
    } else {
        QSqlError err = query.lastError();
        qDebug() << "update statistics error: " << err.text();
    }
    return rez;
}

bool DbTracks::createDayRecord()
{
    qint64 dtInt = QDate::currentDate().startOfDay().toSecsSinceEpoch();
    qint64 dtmInt = QDateTime::currentDateTime().toSecsSinceEpoch();
    QVariantList newRec = {QVariant("NULL"),
                           QVariant(dtInt),
                           QVariant(dtmInt),
                           QVariant(0),
                           QVariant(""),
                           QVariant("")};
    return createRecord(newRec);
}
