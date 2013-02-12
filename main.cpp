#include <QtGui/QApplication>
#include <QSqlDatabase>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Создаём соединение с базой данных
    w.createDbConnection();

//Создаём модель данных терминалов
    terminalModel *mod;
    mod = new terminalModel();

 //Устанавливаем модель для вывода и настраиваем вид таблицы
    w.setTableModelAndHeaders((mod->model));

 //Прикрепляем связаную таблицу к выпадающему списку
  //  w.conBoxWhithRelation(mod->model);

//Прикрепляем строки таблицы к полям ввода
//    w.constructMapper(mod->model);

//Соединяем управляющие кнопки с фунциональными слотами
    w.connectFuncButton(mod);

    //Выводим главное окно
    w.show();
     return a.exec();
}
