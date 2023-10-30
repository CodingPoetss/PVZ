#include "mainwindow.h"
#include "iostream"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    srand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));

    // 创建一个 QMediaPlayer 对象
    QMediaPlayer* sound = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    sound->setAudioOutput(audioOutput);
    if(audioOutput->isMuted()){
        std::cout<<"muted!!!!!!!!!!!!"<<std::endl;
    }else{
        std::cout<<"music is playing"<<std::endl;
    }


    if(sound->hasAudio()){
        std::cout<<"no audio"<<std::endl;
    }else{
        std::cout<<"audio is playing"<<std::endl;
    }

    if(sound->isAvailable()){
        std::cout<<"not available"<<std::endl;
    }else{
        std::cout<<"available"<<std::endl;
    }
    // 设置音频文件的路径（如果位于资源文件中，请使用"qrc:"前缀）
    sound->setSource(QUrl::fromLocalFile("qrc:/music/Grazy Dave.wav"));

    // 设置音量
    audioOutput->setVolume(100); // 0-100，100 表示最大音量

    // 播放音频
    sound->play();

    // 连接信号槽以实现循环播放
    connect(sound, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            sound->setPosition(0); // 将播放位置重置为开始
            sound->play();
        }
    });


    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    Shop *shop = new Shop;
    shop->setPos(520, 45);
    scene->addItem(shop);
    Shovel *shovel = new Shovel;
    shovel->setPos(830, 40);
    scene->addItem(shovel);
    Button *button = new Button(sound, timer);
    button->setPos(970, 20);
    scene->addItem(button);
    Map *map = new Map;
    map->setPos(618, 326);
    scene->addItem(map);
    for (int i = 0; i < 5; ++i)
    {
        Mower *mower = new Mower;
        mower->setPos(210, 130 + 98 * i);
        scene->addItem(mower);
    }
    view = new QGraphicsView(scene, this);
    view->resize(902, 602);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/FutureBackground.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    sound->play();
    timer->start(33);
    view->show();
}

MainWindow::~MainWindow()
{
    delete sound;
    delete timer;
    delete scene;
    delete view;
}

void MainWindow::addZombie()
{
    static int low = 4;
    static int high = 8;
    static int maxtime = 20 * 1000 / 33;
    static int time = maxtime / 2;
    static int counter = 0;
    if (++counter >= time)
    {
        if (++low > high)
        {
            maxtime /= 1.3;
            high *= 2;
        }
        counter = 0;
        time = rand() % (2 * maxtime / 3) + maxtime / 3;
        int type = rand() % 100;
        int i = rand() % 5;
        Zombie *zombie;
        if (type < 40)
            zombie = new BasicZombie;
        else if (type < 70)
            zombie = new ConeZombie;
        else if (type < 80)
            zombie = new BucketZombie;
        else if (type < 90)
            zombie = new ScreenZombie;
        else
            zombie = new FootballZombie;
        zombie->setPos(1028, 130 + 98 * i);
        scene->addItem(zombie);
    }
}

void MainWindow::check()
{
    static int time = 1 * 1000 / 33;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == Zombie::Type && item->x() < 200)
            {
                scene->addPixmap(QPixmap(":/images/ZombiesWon.png"))->setPos(336, 92);
                sound->pause();
                sound->setSource(QUrl::fromLocalFile("qrc:/music/losemusic.mp3"));
                sound->play();
                scene->advance();
                timer->stop();
                return;
            }
    }
}
