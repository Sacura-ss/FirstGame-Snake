#include "GameWidget.h"
#include <QPushButton>
#include <QApplication>
#include <QTime>
#include <QPainter> //для рисования
#include <QFile>



GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(W_WIDTH,W_HEIGHT);

    QPushButton* buttonExit = new QPushButton("Exit", this);
    buttonExit->setGeometry(700, 0, 100, 30);
    buttonExit->setFont(QFont("Decorative", 18, QFont::Bold));

    QObject::connect(buttonExit,&QPushButton::clicked , qApp, &QApplication::quit);

    left_A = false;
    right_D = true;
    up_W = false;
    down_S = false;
    inGame = true;

    counter = 0;

    loadImages();
    initGame();
}

GameWidget::~GameWidget()
{

}

void GameWidget::loadImages(){

    dot.load("/home/luba/qt_project/start0/Images/dot3.png");
    head.load("/home/luba/qt_project/start0/Images/head3.png");
    cherry.load("/home/luba/qt_project/start0/Images/cherry5.png");
    box.load("/home/luba/qt_project/start0/Images/box2.png");

}

void GameWidget::initGame(){
    //размещаем змейку длиной 3 на поле, точнее задаем кординаты ее частей
    //случайным образом определяем позицию на игровом поле, где будет располагаться вишенка
    //запускаем таймер

    dots =3;

    for (int i = 0; i < dots; i++) {
            x[i] = 160 - i * DOT_SIZE;
            y[i] = 80;
        }

     locateCherry();

     timerId = startTimer(DELAY);//запускаем таймер в миллисекундах, DELAY считает в мс
}

void GameWidget::paintEvent(QPaintEvent *e){

    Q_UNUSED(e);
    doDrawing();

}

void GameWidget::doDrawing(){

    QPainter qp(this);//Создание живописца.

    if (inGame) {
        qp.drawImage(cherry_x, cherry_y, cherry);//рисунок  в точке

        if ( dots > 5){
            for(int p = 0; p < amountBox; p++){
                qp.drawImage(box_x[p], box_y[p], box);
            }
        }

        for (int j = 0; j < dots; j++) {
            if (j == 0) {
                qp.drawImage(x[j], y[j], head);
            } else {
                qp.drawImage(x[j], y[j], dot);
            }
        }

    } else {

        gameOver(qp);

    }
}

void GameWidget::gameOver(QPainter &qp){

    QString message = "Game over(";
    QFont font("Decorative", 18, QFont::Bold);

    qp.setPen(QColor(Qt::black));//Устанавливает для пера художника стиль, ширину 1 и указанный цвет.
    qp.setFont(font);

    QString count_str = QString::number( counter,10) ;


    qp.drawText(W_WIDTH/2 - 60, W_HEIGHT/2 - 60, message); //рисует текст в данной

    qp.drawImage(W_WIDTH/2 -20, W_HEIGHT/2 - 30, cherry);
    qp.drawText(W_WIDTH/2 + 40, W_HEIGHT/2, count_str);

}
void GameWidget::checkCherry() {

    if((x[0] == cherry_x ) && (y[0] == cherry_y)){

        dots++;
        counter += 1;
        locateCherry();
        if (dots > 5) {
            locateBox();
        }
    }
}

void GameWidget::move(){

    for (int k = dots; k > 0; k--){
        x[k] = x[(k-1)];
        y[k] = y[(k-1)];
    }

    if (left_A){
        x[0] -= DOT_SIZE;
    }
    if (right_D) {
        x[0] += DOT_SIZE;
    }

    if (up_W) {
        y[0] -= DOT_SIZE;
    }

    if (down_S) {
        y[0] += DOT_SIZE;
     }

}

void GameWidget::checkHit(){
    for (int z = dots; z > 0; z--){
        if ((z>4) && ( x[0] == x[z]) && (y[0]==y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= W_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0){
        inGame = false;
    }

    if (x[0] >= W_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0){
        inGame = false;
    }

    if (dots >5) {

        for(int n = 0; n < amountBox; n++){

            if ((x[0] == box_x[n]) && (y[0] == box_y[n])) {
                inGame = false;
            }
        }

    }


    if(!inGame) {
        killTimer(timerId);
    }

}

void GameWidget::locateCherry(){

    QTime time = QTime::currentTime(); //currentTime() Возвращает текущее время по системным часам.
    qsrand((uint) time.msec());//msec() Возвращает миллисекунду (от 0 до 999) времени.

    int r = qrand() % RAND_POS;
    cherry_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    cherry_y = (r * DOT_SIZE);

}

void GameWidget::locateBox(){
    QTime time = QTime::currentTime(); //currentTime() Возвращает текущее время по системным часам.
    qsrand((uint) time.msec());//msec() Возвращает миллисекунду (от 0 до 999) времени.

    for(int v = 0; v < amountBox; ) {

        int u = qrand() % RAND_POS;
        box_x[v] = (u * DOT_SIZE);

        u = qrand() % RAND_POS;
        box_y[v] = (u * DOT_SIZE);

        if ( ( (box_x[v] == cherry_x) && (box_y[v] == cherry_y) ) || ((box_x[v] == x[0]+DOT_SIZE) || (box_y[v] == y[0]+DOT_SIZE) || (box_x[v] == x[0]-DOT_SIZE)||(box_y[v] == y[0]-DOT_SIZE) )) {

        } else{
            v++;
        }
    }

}

void GameWidget::timerEvent(QTimerEvent *e){

    Q_UNUSED(e);

    if(inGame){

        checkCherry();
        checkHit();
        move();

    }

    repaint();//вызов Paintevent, перерисовки окна

}
void GameWidget::keyPressEvent(QKeyEvent *e){

    int key = e -> key(); //key() Возвращает код клавиши, которая была нажата или отпущена.

    if ((key == Qt::Key_A) && (!right_D)){
        left_A = true;
        up_W = false;
        down_S = false;
    }

    if ((key == Qt::Key_D) && (!left_A)){
        right_D = true;
        up_W = false;
        down_S = false;
    }

    if ((key == Qt::Key_W) && (!down_S)){
        up_W = true;
        right_D = false;
        left_A = false;
    }

    if ((key == Qt::Key_S) && (!up_W)){
        down_S = true;
        right_D = false;
        left_A = false;
    }

    QWidget::keyPressEvent(e);
}







