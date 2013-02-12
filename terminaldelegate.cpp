#include "terminaldelegate.h"
#include <QtGui>

terminalDelegate::terminalDelegate(QObject *parent): QSqlRelationalDelegate(parent)
{
}
void terminalDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    if (index.column() != 3) {
        QSqlRelationalDelegate::paint(painter, option, index);
    } else {
        const QAbstractItemModel *model = index.model();
        QStyleOptionViewItem opt = QStyleOptionViewItem(option);
        int width = 22;
        int height = 22;
        int x = opt.rect.x();
        int y = opt.rect.y()+4;
        opt.rect = QRect(x, y, width, height);
             if(model->data(index).toBool())
            opt.state = QStyle::State_On;
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &opt, painter);
        }
       // drawFocus(painter, option, option.rect.adjusted(0, 0, -1, -1)); // since we draw the grid ourselves


}

QSize terminalDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
 /*   if (index.column() == 3)
        return QSize(5 * star.width(), star.height()) + QSize(1, 1);
*/
    return QSqlRelationalDelegate::sizeHint(option, index) + QSize(1, 1); // since we draw the grid ourselves
}

bool terminalDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index)
{
        return QSqlRelationalDelegate::editorEvent(event, model, option, index);
}

QWidget *terminalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    if (index.column() != 3)
        return QSqlRelationalDelegate::createEditor(parent, option, index);

    // for editing the year, return a spinbox with a range from -1000 to 2100.
    QCheckBox *sb = new QCheckBox(QString(""),(parent));
    const QAbstractItemModel *model = index.model();
    sb->setChecked(model->data(index).toBool());
    return sb;
}
