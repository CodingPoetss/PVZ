#include "cherrybomb.h"
#include <QTimer>

CherryBomb::CherryBomb()
{
    atk = 1800;
    hp = 300;
    setMovie(":/images/CherryBomb.gif");
}

QRectF CherryBomb::boundingRect() const
{
    return state ? QRectF(-150, -150, 300, 300) : Plant::boundingRect();
}

void CherryBomb::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else if (state == 0 && movie->currentFrameNumber() == movie->frameCount() - 1)
    {
        state = 1;
        setMovie(":/images/Boom.gif");

        // 创建一个 QMediaPlayer 对象
        sound->setSource(QUrl::fromLocalFile("qrc:/music/cherrybomb.mp3"));
        sound->play();

        QList<QGraphicsItem *> items = collidingItems();
        foreach (QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            zombie->setMovie(":/images/Burn.gif");
            QTimer *timer = new QTimer;
            timer->setSingleShot(true);
            timer->setInterval(200); // 500毫秒（0.5秒）后停止效果
            QObject::connect(timer, &QTimer::timeout, [=]() {
                delete zombie;
                delete timer; // 删除定时器
            });
            timer->start();
        }
    }
    else if (state == 1 && movie->currentFrameNumber() == movie->frameCount() - 1)
        delete this;
}

bool CherryBomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && QLineF(pos(), other->pos()).length() < 160;
}
