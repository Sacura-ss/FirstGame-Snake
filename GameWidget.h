#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    virtual ~GameWidget();//деструктор virtual!!!

protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

private:
    QImage dot;
    QImage head;
    QImage cherry;
    QImage box;

    static const int W_WIDTH = 800;
    static const int W_HEIGHT = 800;
    static const int DOT_SIZE = 40; //размер яблока и "частей" тела змеи
    static const int ALL_DOTS = 6400; //максимально количество возможных точек на доске
    static const int RAND_POS = 18; // используется для вычисления случайной позиции вишни
    static const int DELAY = 200; // определяет скорость игры
    static const int amountBox = 5;

    int timerId;
    int dots; //длина змеи
    int cherry_x;
    int cherry_y;
    int box_x[amountBox];
    int box_y[amountBox];
    int counter = 0;


    int x[ALL_DOTS]; //содержат координаты (x;y) всех «частей» тела змеи
    int y[ALL_DOTS];

    bool left_A;
    bool right_D;
    bool up_W;
    bool down_S;
    bool inGame;

    void loadImages();
    void initGame();
    void locateCherry();
    void locateBox();
    void checkCherry();
    void checkHit();
    void move();
    void doDrawing();
    void gameOver(QPainter &);



};

#endif // GAMEWIDGET_H
