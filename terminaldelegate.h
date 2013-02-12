#ifndef TERMINALDELEGATE_H
#define TERMINALDELEGATE_H

#include <QSqlRelationalDelegate>
#include <QCheckBox>
#include <QtGui/QApplication>

class terminalDelegate : public QSqlRelationalDelegate
{
public:
    terminalDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const;
};

#endif // TERMINALDELEGATE_H
