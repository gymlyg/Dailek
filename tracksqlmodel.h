#ifndef TRACKSQLMODEL_H
#define TRACKSQLMODEL_H

#include <QSqlQueryModel>

class TrackSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit TrackSqlModel(QObject *parent = nullptr);
    void setSelQuery(QDate &dt);
    void setTodaySelQuery();
    void selQuery();
private:
    QString m_sSelQuery;
    bool setData(const QModelIndex &index, const QVariant &value, int nRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;


};

#endif // TRACKSQLMODEL_H
