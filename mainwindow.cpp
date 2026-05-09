#include <QTimer>
#include <QPushButton>

#include "mainwindow.h"
#include <QLabel>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);
/// Your code here...

    const int sizeBut = 20;
    auto GlobalGen = QRandomGenerator::global();
    auto globtimer = new QTimer();
    globtimer->setInterval(100);
    globtimer->start();
    auto spawnTimer = new QTimer();
    spawnTimer->setInterval(GlobalGen->bounded(100, 1000));
    spawnTimer->start();
    connect(spawnTimer, &QTimer::timeout,
            [this, GlobalGen, globtimer]{
                int x = GlobalGen->bounded(width()-sizeBut);
                int y = GlobalGen->bounded(100);
                int speed = GlobalGen->bounded(1, 6);
                auto *snowflake = new QPushButton("*", this);
                snowflake->setGeometry(x, y, sizeBut, sizeBut);
                snowflake->show();

                connect(globtimer, &QTimer::timeout, snowflake,
                        [this, speed, snowflake] {
                            if (snowflake->underMouse())
                                snowflake->move(snowflake->pos().x(), snowflake->pos().y() + speed*2);
                            else
                                snowflake->move(snowflake->pos().x(), snowflake->pos().y() + speed);

                            if(snowflake->pos().y()>height())
                            {
                                snowflake->deleteLater();
                                setStyleSheet("background-color: red");
                            }
                });

                connect(snowflake, &QPushButton::clicked, this,
                        [snowflake] {
                            snowflake->deleteLater();
                        });
            });






}

MainWindow::~MainWindow()
{
}
