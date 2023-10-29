#ifndef SHOVEL_H
#define SHOVEL_H

#include "other.h"
#include "plant.h"

class Shovel : public Other
{
public:
    Shovel();
    ~Shovel();
    QRectF boundingRect() const override;
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    QMediaPlayer* sound_remove = new QMediaPlayer();
    QAudioOutput* audioOutput_remove = new QAudioOutput();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void removePlant(QPointF pos);
};

#endif // SHOVEL_H
