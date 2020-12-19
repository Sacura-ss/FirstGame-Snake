#include "MyWidget.h"
#include "GameWidget.h"
#include <QPushButton>
#include <QApplication>


MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    int width = 800;
    int height = 800;
    setFixedSize(width,height);

    //создаем и настраиваем дочерниt виджеты
    QPushButton* buttonExit = new QPushButton("Exit", this);
        //координаты кнопки(по умол 0,0) (координаты х и у верхнего левого угла,ширина и высота кнопки)
    buttonExit->setGeometry(700, 0, 100, 30);
    buttonExit->setFont(QFont("Decorative", 18, QFont::Bold));

    QObject::connect(buttonExit,&QPushButton::clicked , qApp, &QApplication::quit);

    QPushButton* buttonStart = new QPushButton("Start",this);
    buttonStart->setGeometry(200,300,400,200);
    buttonStart->setFont(QFont("Decorative", 18, QFont::Bold));

    QObject::connect(buttonStart,&QPushButton::clicked ,this, &MyWidget::StartPush);
}

MyWidget::~MyWidget()
{
   delete _gameWindow;
}
void MyWidget::StartPush(){
     hide();//функция делает убирает предыдущее окно
    _gameWindow = new GameWidget();
    _gameWindow->show();
}
