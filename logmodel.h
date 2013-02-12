#ifndef LOGMODEL_H
#define LOGMODEL_H
#include <QtSql>

class logModel : public QObject
{
    Q_OBJECT
public:
    logModel();
    QSqlRelationalTableModel  log_mod;
public slots:
    void addInsLog(QSqlRecord&);
    void addUpdLog(int, QSqlRecord&);
    void addDelLog (int);
    void clearLog();
private:
    void createLogTable();
    void setLogFiels(QSqlRecord&, QString);

};

#endif // LOGMODEL_H
