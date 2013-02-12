#ifndef TERMINALMODEL_H
#define TERMINALMODEL_H
#include <QtSql>
#include "logmodel.h"

class terminalModel : public QObject
{
    Q_OBJECT
public:
    terminalModel();
    QSqlRelationalTableModel& getModel();
    void createConnection();
    QSqlRelationalTableModel model;
    logModel lgmod;
public slots:
    void addRow();
    void canDeleteRows(QModelIndexList);
signals:
    void afterDelete(int);
private:
    void createTerminalTable();
    void createAllTerminalTable();
    void createLocationTable();
    void consModelHeaders(int);
    void conBeforeEventsAndLogs();
    void createDepartmentTable();
    void createCompanyTable();
    void createLocationView();
};


    /*


    bool createConnection();
    void submit();
    void add();
    void createTerminalTable();

private:
    QSqlRelationalTableModel model;
};
*/
#endif // TERMINALMODEL_H
