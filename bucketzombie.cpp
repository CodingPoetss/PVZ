#include "bucketzombie.h"

BucketZombie::BucketZombie()
{
    hp = 1370;
    atk = 100 * 33 / 1000;
    speed = 80.0 * 33 / 1000 / 4.7;
    setMovie(":/images/Xiucai.gif");
}

void BucketZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/images/ZombieDie.gif");
            setHead(":/images/ZombieHead.gif");
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
        plant->hp -= atk;
        if (state != 1)
        {
            sound->setSource(QUrl::fromLocalFile("qrc:/music/chomp.mp3"));
            sound->setLoops(100);
            sound->play();
            state = 1;
            setMovie(":/images/XiucaiEat.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;       

        setMovie(":/images/Xiucai.gif");
        sound->pause();

    }
    setX(x() - speed);
}
