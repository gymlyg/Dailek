#ifndef TRACKSDELEGATE_H
#define TRACKSDELEGATE_H

#include <QStyledItemDelegate>

class TracksDelegate : public QStyledItemDelegate
{
public:
    TracksDelegate();
    void paint(QPainter *painter
                , const QStyleOptionViewItem &option
                , const QModelIndex &index) const;
};

#endif // TRACKSDELEGATE_H
