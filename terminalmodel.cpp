#include "terminalmodel.h"
#include "mainwindow.h"
#include <QtSql>
#include "logmodel.h"

terminalModel::terminalModel()
{
createLocationView();
         //   this->createConnection();
    //Сохранение изменений таблицы после подтверждения
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);

    //Проверяем наличие таблицы с адресами
    model.setTable("departloc");
    if(model.select())
        qDebug()<<("Ok! LOcation table is here!");
    else
    {
        //Если к таблице нельзя подключится, создаём свою.
        qDebug()<<("Error! Cant find location table!");
        createLocationTable();
    }

    model.setTable("terminals_table");
        if(model.select())
        qDebug()<<("Ok! Terminals table is here too!");
    else
    {
        qDebug()<<("Error! Cant find terminal table!");
        createTerminalTable();
        model.setTable("terminals_table");
        model.select();
    }

    //Узнаём индекс поля с местоположения
    int locationIdx = model.fieldIndex("location_id");

        // Устанавливаем связь с таблицей адресов
    model.setRelation(locationIdx, QSqlRelation("departloc", "id", "adress"));

        //Настраиваем шапку таблицы
    consModelHeaders(locationIdx);

    //Создаём соединения для записи логов
    conBeforeEventsAndLogs();
}



//Слот добавления строки
void terminalModel::addRow()
{
   this->model.insertRow(this->model.rowCount());
}

//Удаление выделенных строк
void terminalModel::canDeleteRows(QModelIndexList rows)
{
    for( int i=0; i<rows.count(); i++)
    if(!this->model.removeRow(rows.at(i).row()))
        qDebug()<<("Ошибка удаления данных! Error! Cant delete row! ")<<this->model.lastError();
    else
        emit afterDelete(rows.at(i).row());

}

//Создание таблицы
    void terminalModel::createAllTerminalTable(){
        this->createTerminalTable();
        this->createLocationTable();
    }
    void terminalModel::createTerminalTable()
    {
        QSqlQuery query;
        QString str ="CREATE TABLE terminals_table("
                "id INTEGER PRIMARY KEY, "
                "serial TEXT,"
                "system_ind TEXT,"
                "state text,"
                "location_id INT);";

        QString insrt = "INSERT INTO terminals_table (id, serial, system_ind, state, location_id) VALUES(1, 'serial-number1','sys1', 'false', 0);";
        QString insrt2 = "INSERT INTO terminals_table (id, serial, system_ind, state, location_id) VALUES(2, 'serial-num2','system-2', 'true', 2);";
        QString insrt3 = "INSERT INTO terminals_table (id, serial, system_ind, state, location_id) VALUES(3, 'serial-3','system-id3', 'false', 1);";

      if(!query.exec(str)){
            qDebug()<<("Create insert error!!!")<<query.lastError();
         }
      else
          qDebug()<<("Ok! Terminal Table sucsses Create!");
      if(!query.exec(insrt)){
            qDebug()<<("Terminal table insert error!!!")<<query.lastError();
         }
      else
          qDebug()<<("Ok! Row sucssesfuly insert!!!");
        query.exec(insrt2);
        query.exec(insrt3);

}
    void terminalModel::createLocationTable()
    {
        createDepartmentTable();
        createCompanyTable();
        createLocationView();
    }

    void terminalModel::createDepartmentTable()
    {
        QSqlQuery query;
        QString str ="CREATE TABLE department_adress("
                "id INTEGER PRIMARY KEY, "
                "adress TEXT,"
                "company_id INT);";

        QString insrt = "INSERT INTO department_adress (id, adress, company_id) VALUES(0, 'Sales outlet 32', 2);";
        QString insrt1 = "INSERT INTO department_adress (id, adress, company_id) VALUES(1, 'Sklad', 2);";
        QString insrt2 = "INSERT INTO department_adress (id, adress, company_id) VALUES(2, 'Office', 0);";
        QString insrt3 = "INSERT INTO department_adress (id, adress, company_id) VALUES(3, 'Repair department', 1);";

      if(!query.exec(str)){
            qDebug()<<("Create location table error!!!")<<query.lastError();
         }
      else
          qDebug()<<("Ok! Location Table sucsses Create!");
      if(!query.exec(insrt)){
            qDebug()<<("Location Table insert error!!!")<<query.lastError();
         }
      else
          qDebug()<<("Ok! Location Row sucssesfuly insert!!!");
      query.exec(insrt1);
      query.exec(insrt2);
      query.exec(insrt3);
}
    void terminalModel::createCompanyTable()
    {
        QSqlQuery query;
        QString str ="CREATE TABLE company("
                "id INTEGER PRIMARY KEY, "
                "name TEXT);";

        QString insrt = "INSERT INTO company (id, name) VALUES(0, 'ChameleonSoft');";
        QString insrt2 = "INSERT INTO company (id, name) VALUES(1, 'Bankcomlink');";
        QString insrt3 = "INSERT INTO company (id, name) VALUES(2, 'Chestnut');";

      if(!query.exec(str)){
            qDebug()<<("Create location table error!!!")<<query.lastError();
         }
      else
          qDebug()<<("Ok! Location Table sucsses Create!");
      if(!query.exec(insrt)){
            qDebug()<<("Location Table insert error!!!")<<query.lastError();
         }
      else
          qDebug()<<("Ok! Location Row sucssesfuly insert!!!");
      query.exec(insrt2);
      query.exec(insrt3);

      }
    void terminalModel::createLocationView()
    {
        QSqlQuery query;
        QString str ="CREATE VIEW IF NOT EXISTS departloc "
                "AS SELECT department_adress.id AS 'id', company.name||', '||department_adress.adress AS 'adress' "
                "FROM department_adress, company WHERE department_adress.company_id = company.id";
        if(!query.exec(str))
              qDebug()<<("Create location view error!!!")<<query.lastError();
    }
    void terminalModel::consModelHeaders(int locationIdx){
        model.setHeaderData(locationIdx, Qt::Horizontal, tr("Location"));
        model.setHeaderData(model.fieldIndex("serial"), Qt::Horizontal, tr("serial"));
        model.setHeaderData(model.fieldIndex("system_ind"), Qt::Horizontal, tr("system id"));
        model.setHeaderData(model.fieldIndex("state"), Qt::Horizontal, tr("state"));
    }
    void terminalModel::conBeforeEventsAndLogs(){
    connect(&model, SIGNAL(beforeDelete(int)), &lgmod, SLOT(addDelLog(int)));
    connect(&model, SIGNAL(beforeUpdate(int,QSqlRecord&)), &lgmod, SLOT(addUpdLog(int,QSqlRecord&)));
    connect(&model, SIGNAL(beforeInsert(QSqlRecord&)), &lgmod, SLOT(addInsLog(QSqlRecord&)));
    }
