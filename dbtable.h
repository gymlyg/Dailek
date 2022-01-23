#ifndef DBTABLE_H
#define DBTABLE_H

#include <QString>
#include <QStringList>
#include <QVariantList>

class DbTable
{
public:
    DbTable(const QString &tableName, const QStringList &tracksFields);
    QString m_sTableName;
    QStringList m_slTracksFields = {
    };
    enum fields {
        FIELD_NAME,
        FIELD_TYPE
    };
    enum prep {
        PREP_FIELD_NAMES,
        PREP_VALUES,
    };
    bool init();
    static bool createTable(const QString &tableName, const QStringList &fieldsData);
    static QStringList prepareValues(const QStringList &fieldsData, const QVariantList &values);
    bool createRecord(const QVariantList &values);
};

#endif // DBTABLE_H
