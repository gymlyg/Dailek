#include "tracksqlmodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

TrackSqlModel::TrackSqlModel(QObject *parent) : QSqlQueryModel(parent)
{
    QDate dt = QDate::currentDate();
    QString deltaField = "CASE WHEN (time_end - time_start) <= 0 THEN 0 ELSE (time_end - time_start) END";
    QString query = "select id, time_start, time_end, %1, task_target, task_desc from tracks where date_current_day = %2";
    query = query.arg(deltaField).arg(dt.startOfDay().toSecsSinceEpoch());
    qDebug() << "sel q:" << query;
    setSelQuery(query);
}

bool TrackSqlModel::setData(const QModelIndex &index, const QVariant &value, int nRole)
{
    bool rez = false;
    int id = 0, column = 0;
    QSqlQuery q;
    QString str;

    if(index.isValid() && Qt::EditRole == nRole) {
        id = index.siblingAtColumn(0).data(Qt::EditRole).toInt();
        column = index.column();
        if(5 == column) {
            str = QString("update tracks set task_desc='%1' where id=%2").arg(value.toString()).arg(id);
            rez = q.exec(str);
        } else if (2 == column) {
            str = QString("update tasks set amount=%1 where id=%2").arg(value.toInt()).arg(id);
            rez = q.exec(str);
        }
        if(rez) {
            this->setQuery(m_sSelQuery);
            emit dataChanged(index, index);
        } else {
            QSqlError sr = q.lastError();
            qDebug() << "err:" << sr.text();
        }
    }
    return rez;
}

Qt::ItemFlags TrackSqlModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(index.isValid())
        return flags | Qt::ItemIsEditable;
    return flags;
}

void TrackSqlModel::setSelQuery(QString query)
{
    m_sSelQuery = query;
}

void TrackSqlModel::selQuery()
{
    setQuery(m_sSelQuery);
}
