#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include "shop.h"
#include "card.h"
#include "shovel.h"
#include "button.h"
#include "map.h"
#include "mower.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void addZombie();
    void check();
private:
    // 创建一个 QMediaPlayer 对象
    QMediaPlayer* sound = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QLabel* gameOverLabel;
    QMovie* gif;

};

#endif // MAINWINDOW_H
