#include "dbtable.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

DbTable::DbTable(const QString &tableName, const QStringList &tracksFields):
    m_sTableName(tableName),
    m_slTracksFields(tracksFields)
{

}

bool DbTable::init()
{
    return createTable(m_sTableName, m_slTracksFields);
}

bool DbTable::createTable(const QString &tableName, const QStringList &fieldsData)
{
    QSqlQuery query;
    QString qStr = "CREATE TABLE IF NOT EXISTS %1(%2)";
    qStr = qStr.arg(tableName).arg(fieldsData.join(","));
    qDebug() << "query: " << qStr;
    bool r = query.exec(qStr);
    if(!r) {
        QSqlError err = query.lastError();
        qDebug() << "creating table error: " << err.text();
    }
    return r;
}

bool DbTable::createRecord(const QVariantList &values)
{
    QSqlQuery query;
    QString qStr = "INSERT INTO %1 (%2) VALUES (%3)";

    QStringList qData = prepareValues(m_slTracksFields, values);

    qStr = qStr.arg(m_sTableName)
            .arg(qData[PREP_FIELD_NAMES])
            .arg(qData[PREP_VALUES]);
    qDebug() << "query: " << qStr;
    bool r = query.exec(qStr);
    if(!r) {
        QSqlError err = query.lastError();
        qDebug() << "creating table error: " << err.text();
    }
    return r;
}

QStringList DbTable::prepareValues(const QStringList &fieldsData, const QVariantList& values)
{
    QString valuesStr;
    QStringList fieldsStrLst, valuesStrLst, curFieldList;
    for(int i = 0; i < fieldsData.size(); i++) {
        curFieldList = fieldsData.at(i).split(" ");
        valuesStr = values.at(i).toString();
        if(curFieldList[FIELD_TYPE].contains("text")
                || curFieldList[FIELD_TYPE].contains("varchar")) {
            valuesStr = "'" + valuesStr + "'";
        }
        fieldsStrLst.append(curFieldList[FIELD_NAME]);
        valuesStrLst.append(valuesStr);
    }
    return QStringList({fieldsStrLst.join(", "), valuesStrLst.join(", ")});
}
