#ifndef BLASTPEA_H
#define BLASTPEA_H

#include "other.h"

class BlastPea : public Other
{
public:
    BlastPea(int attack = 0, bool flag = false);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
private:
    bool snow;
    int atk;
    qreal speed;
    QMovie* gif;
};

#endif // BLASTPEA_H
