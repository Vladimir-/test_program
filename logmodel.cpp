#include "logmodel.h"
#include <QtSql>

logModel::logModel()
{
    log_mod.setTable("terminal_log");
    if(log_mod.select())
        qDebug()<<("Ok! Log table is here!");
    else
    {
        //≈сли к таблице невозможно подключитс€, создаЄм свою.
        qDebug()<<("Error! Cant Set table!");
        createLogTable();
        log_mod.setTable("terminal_log");
        log_mod.select();
        log_mod.setRelation(log_mod.fieldIndex("location_id"), QSqlRelation("departloc", "id", "adress"));

    }
}

void logModel::createLogTable(){
    QSqlQuery q;
    if (!q.exec(QLatin1String("create table terminal_log(id integer primary key, action varchar,  date varchar, terminal_id integer, serial varchar, system_ind varchar, state integer, location_id integer)")))
        qDebug()<<("Error! Cant create new log table! ")<< q.lastError();
}

void logModel::addInsLog(QSqlRecord& terminal)
{
    QSqlRecord termlog;
    termlog = terminal;
    setLogFiels(termlog, QString("INSERT"));
    this->log_mod.insertRecord(-1, termlog);
}
void logModel::addUpdLog(int row, QSqlRecord& terminal)
{
    QSqlRecord termlog;
    termlog = terminal;
    //находим индекс пол€ айди
    int idix = termlog.indexOf("id");
    //создаЄм новое поле
    QSqlField terId;
    terId.setName(QString("terminal_id"));
    terId.setValue(row);
    //замен€ем старое поле новым
    termlog.replace(idix, terId);
    //добавл€ем поле с названием выполн€емого действи€
    setLogFiels(termlog, QString("UPDATE"));
    this->log_mod.insertRecord(-1, termlog);
}
void logModel::addDelLog(int row)
{
    QSqlRecord termlog;
    termlog.append(QSqlField(QString("terminal_id"), QVariant::Int));
    termlog.setValue(QString("terminal_id"), row);
    setLogFiels(termlog, QString("DELETE"));
    this->log_mod.insertRecord(-1, termlog);
}

void logModel::setLogFiels(QSqlRecord& logRec, QString action){
    //????????? ???? ????????
    logRec.append(QSqlField(QString("action"), QVariant::String));
    logRec.setValue(QString("action"), action);
    //????????? ???? ????
    logRec.append(QSqlField(QString("date"), QVariant::String));
    logRec.setValue(QString("date"), QString(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")));
}
void logModel::clearLog(){
    this->log_mod.clear();
    QSqlQuery q;
    if (!q.exec(QLatin1String("drop  table if exists terminal_log")))
        qDebug()<<("Error! Cant create new log table! ")<< q.lastError();
}

