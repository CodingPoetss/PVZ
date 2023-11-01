#include "repeater.h"

Cherryshooter::Cherryshooter()
{
    atk = 25;
    hp = 300;
    time = int(2.5 * 1000 / 33);
    setMovie(":/images/CherryShooter.gif");
}

void Cherryshooter::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        QList<QGraphicsItem *> items = collidingItems();
        if (!collidingItems().isEmpty())
        {
            BlastPea *blastpea = new BlastPea(atk);
            blastpea->setX(x() + 32);
            blastpea->setY(y());
            scene()->addItem(blastpea);
            return;
        }
    }
}

bool Cherryshooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y());
}
