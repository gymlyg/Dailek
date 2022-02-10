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
    QSqlQuery query;
    qint64 iCurDtTm = QDateTime::currentDateTime().toSecsSinceEpoch();
    qint64 iStDayDt = QDate::currentDate().startOfDay().toSecsSinceEpoch();
    //QString qStr = "UPDATE %1 set time_end = %2 WHERE id = (SELECT id FROM %1 ORDER BY id DESC LIMIT 1)";
    QString lastRecord = "SELECT * FROM %1 ORDER BY id DESC LIMIT 1";
    if(query.exec(lastRecord)) {
        QSqlRecord record = query.record();
        if(query.next()) {
            if(record.count() > 4) {
                int taskId = query.value(0).toInt();
                int taskSt = query.value(1).toInt();
                QString taskType = query.value(2).toString();
                QString taskDesc = query.value(3).toString();

                if(taskSt < iStDayDt) {
                    QVariantList newRec = {QVariant("NULL"),
                                           QVariant(0),
                                           QVariant(iStDayDt),
                                           QVariant(iCurDtTm),
                                           QVariant(taskType),
                                           QVariant(taskDesc)};
                    qDebug()<<" create new day part: " << newRec;
                    if(!createRecord(newRec))
                        return false;
                }

                lastRecord = "UPDATE %1 set time_end = %2 WHERE id = %3";
                lastRecord = lastRecord.arg(m_sTableName, iStDayDt, taskId);
                qDebug() << "last tm update query: " << lastRecord;
                return  query.exec(lastRecord);
            }
        }
    }
    return false;
}

bool DbTracks::updateStatistics(QStringList &statData)
{
    bool rez = false;
    QSqlQuery query;
    QDate dt = QDate::currentDate();
    QString qStr = "select task_target, sum(time_end - time_start) from %1 where date_current_day = %2 and (time_end <> 0 or time_end <> NULL) group by task_target";
    qStr = qStr.arg(m_sTableName).arg(dt.startOfDay().toSecsSinceEpoch());
    qDebug() << qStr;
    rez = query.exec(qStr);
    if(rez) {
        QSqlRecord record = query.record();
        while(query.next()) {
            qDebug() << record << ", amount: " << record;
            if(record.count() > 1) {
                QString taskName = query.value(0).toString();
                int c = query.value(1).toInt();
                int h = c / 3600;
                int m = c % 3600 / 60;
                QString dateString = QString("%1 - %2:%3")
                        .arg(taskName)
                        .arg(h, 2, 'g', -1, '0')
                        .arg(m, 2, 'g', -1, '0');
                statData.append(dateString);
                qDebug() << "append " << dateString;
            }
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
