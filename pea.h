#ifndef PEA_H
#define PEA_H

#include "other.h"

class Pea : public Other
{
public:
    Pea(int attack = 0, bool flag = false);
    ~Pea();
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
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

#endif // PEA_H
