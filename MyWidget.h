#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "GameWidget.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
     MyWidget(QWidget *parent = nullptr); //нулевой указатель для создания окна верхнего уровня
     virtual ~MyWidget();//деструктор virtual!!!
      void StartPush();
private:
      GameWidget* _gameWindow = nullptr;
};




#endif // MYCLASS_H
