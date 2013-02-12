#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataWidgetMapper>
#include <QtSql>
#include <QMessageBox>
#include "logview.h"
#include "terminaldelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::deleteSelectedRows(){
    QModelIndexList rows = ui->terminalTable->selectionModel()->selectedRows();
    emit deleteThisRows(rows);
}
void MainWindow::createDbConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("terminals");
    if (!db.open()) {
        QMessageBox::critical(this, "Can't connect database!",
              QString("Cant connect to database! ")+db.lastError().text());
             }
    if(db.tables().empty())
    {
        QMessageBox::critical(this, "Tables not found", QString("Can't find any table! ") + db.lastError().text());
    }
}
void MainWindow::showLogPlease()
{
    logView *logDialog = new logView;
    logDialog->show();
}
void MainWindow::setTableModelAndHeaders(QSqlRelationalTableModel& model){
    ui->terminalTable->setModel(&model);
    ui->terminalTable->setItemDelegate(new terminalDelegate(ui->terminalTable));

    ui->terminalTable->setColumnHidden(model.fieldIndex("id"), true);
    ui->terminalTable->setSelectionMode(QAbstractItemView::SingleSelection);


}

void MainWindow::connectFuncButton(terminalModel*& mod){
//?????????? ??????
    connect(ui->addButton, SIGNAL(clicked()), mod, SLOT(addRow()));
    //???????? ??????
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteSelectedRows()));
    //????????????? ?????????
    connect(ui->submitButton, SIGNAL(clicked()), &(mod->model), SLOT(submitAll()));
    //???????? ??????, ????? ???? ??? ?????? ????? ?????? ????????
    connect(this, SIGNAL(deleteThisRows(QModelIndexList)), mod, SLOT(canDeleteRows(QModelIndexList)));
    //????? ?????
    connect(ui->logButton, SIGNAL(clicked()), this, SLOT(showLogPlease()));
    connect(this, SIGNAL(onTableLoad()), &(mod->model), SLOT(submitAll()));

    modelUpdate();
}
void MainWindow::modelUpdate(){
    //Send signal for model update
    emit onTableLoad();
    ui->terminalTable->resizeColumnsToContents();
}
