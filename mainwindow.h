#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "terminalmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createDbConnection();
    void setTableModelAndHeaders(QSqlRelationalTableModel&);
    void connectFuncButton(terminalModel*&);
public slots:
    void deleteSelectedRows();
    void showLogPlease();
signals:
    void deleteThisRows(QModelIndexList);
    void onTableLoad();
private:
    void modelUpdate();
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
