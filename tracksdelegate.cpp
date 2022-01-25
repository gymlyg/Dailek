#include "tracksdelegate.h"

#include <QApplication>
#include <QStyledItemDelegate>
#include <QDateTime>
#include <QTime>
#include <QDebug>

TracksDelegate::TracksDelegate()
{

}

void TracksDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    if( 1 == col || 2 == col) {
        int c = index.data().toInt();
        QRect rect = option.rect;
        QString dateString = "-";
        if(c != 0) {
            QDateTime creationDate;
            creationDate.setSecsSinceEpoch(c);
            dateString = creationDate.toString("HH:mm");
        }
        QApplication::style()->drawItemText( painter, rect
                                             , Qt::AlignHCenter | Qt::AlignVCenter
                                             , option.palette, true, dateString );

    } else if( 3 == col) {

        int c = index.data().toInt();
        int h = c / 3600;
        int m = c % 3600 / 60;
        QRect rect = option.rect;

        QString dateString = "%1:%2";
        QApplication::style()->drawItemText( painter, rect
                                             , Qt::AlignHCenter | Qt::AlignVCenter
                                             , option.palette, true
                                             , dateString.arg(h, 2, 'g', -1, '0').arg(m, 2, 'g', -1, '0'));

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
