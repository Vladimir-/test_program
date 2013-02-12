#ifndef QIVBCHECKINDICATORDELEGATE_H
#define QIVBCHECKINDICATORDELEGATE_H

#include "qivbstatedata.h"
#include <QAbstractItemDelegate>


/*!
    \class QivbCheckIndicatorDelegate qivbcheckindicatordelegate.h "qivbcheckindicatordelegate.h"
    \brief Класс-делегат имитирующий поведение виджета QCheckBox.
 */
class QivbCheckIndicatorDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(QivbCheckIndicatorDelegate);
public:
    explicit QivbCheckIndicatorDelegate(QObject * parent = 0);
    virtual ~QivbCheckIndicatorDelegate();

    virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
                       const QModelIndex & index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem & option,
                       const QModelIndex & index) const;
    virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
                       const QStyleOptionViewItem & option, const QModelIndex & index);
signals:
    void checkChanged(bool state, const QModelIndex &);
private:
    StateData state;
    QRect checkRect(const QStyleOptionViewItem & option) const;
};

#endif // QIVBCHECKINDICATORDELEGATE_H
