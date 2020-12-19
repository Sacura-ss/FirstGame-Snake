#include "mainwindow.h"
#include "MyWidget.h"
#include "GameWidget.h"
#include <QApplication> //описание класса QApplication, управляет ресурсами приложухи, шрифт по умол и курсор
//#include <QLabel> // отвечает за текстовые надписи
#include <QPushButton> //графическая кнопка
#include <QFont>
#include <QWidget>//пользовательский интерфейс



int main(int argc, char *argv[]) //argc - количество аргументов командной строки, а argv - массив этих аргументов
{
    QApplication a(argc, argv);

    //создаем виджет, не встроенный в родительский - окно
    MyWidget startWindow;
    //родительский виджет становится видимым, это делает видимыми и все его дочерние виджеты
    startWindow.show();
    return a.exec();
}


