#include "blastpea.h"
#include "zombie.h"
#include "cherrybomb.h"

BlastPea::BlastPea(int attack, bool flag)
{
    snow = flag;
    atk = attack;
    speed = 360 * 33 / 1000;

    gif = new QMovie(snow ? ":/images/basketballsnow.gif" : ":/images/basketball.gif");
    gif->start();
}

QRectF BlastPea::boundingRect() const
{
    return QRectF(-12, -28, 24, 24);
}

void BlastPea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // 创建一个QMovie对象并设置GIF图像的路径
    //QMovie movie(snow ? ":/images/basketballsnow.gif" : ":/images/basketball.gif");

    // 获取GIF图像的帧
    QPixmap frame = gif->currentPixmap();

    // 绘制帧到指定位置
    painter->drawPixmap(QRect(-12, -28, 24, 24), frame);
    //painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(snow ? ":/images/BasketBallSnow.png" : ":/images/BasketBall .png"));
}

bool BlastPea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

void BlastPea::advance(int phase)
{
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[rand() % items.size()]);
        CherryBomb *cherryBomb = new CherryBomb(); // 创建一个新的樱桃炸弹对象
        cherryBomb->setPos(x(), y()); // 设置樱桃炸弹的位置与豌豆射手相同
        scene()->addItem(cherryBomb);
        zombie->hp -= atk;

        delete this;
        return;
    }
    setX(x() + speed);
    if (x() > 1069)
        delete this;
}
